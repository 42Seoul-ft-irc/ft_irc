#include "Server.hpp"

/* 생성자 */
static int convert_port(char *portStr)
{
	for (size_t i = 0; i < strlen(portStr); i++)
		if (!isdigit(portStr[i]))
			throw std::invalid_argument("Error: invalid argument");

	int port = atoi(portStr);

	if (port < 0 || 65535 < port)
		throw std::invalid_argument("Error: invalid argument");

	return port;
}

void create_socket(Server &server)
{
	int socket_fd = socket(AF_INET, SOCK_STREAM, 0);

	if (socket_fd == -1)
		throw std::runtime_error("socket error");

	server.setSocketFd(socket_fd);
}

void Server::open_server(){
	create_socket(*this);

	try
	{
		// 소켓 포트 연결
		struct sockaddr_in server_addr;

		std::memset(&server_addr, 0, sizeof(server_addr));
		server_addr.sin_family = AF_INET;
		server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
		server_addr.sin_port = htons(this->getPortNum());

		if (bind(this->getSocketFd(), reinterpret_cast<const struct sockaddr *>(&server_addr), sizeof(server_addr)) == -1)
			throw std::runtime_error("Error: bind error");

		if (listen(this->getSocketFd(), SOMAXCONN) == -1)
			throw std::runtime_error("Error: listen error");
	}
	catch (const std::exception &e)
	{
		close(this->getSocketFd());
		throw std::runtime_error(e.what());
	}
}

Server::Server(int argc, char **argv) {
	pollfd pollfd;

	if (argc != 3)
		throw std::invalid_argument("Error: invalid argument");
	this->setPortNum(convert_port(argv[1]));
	std::string password(argv[2]);
	this->setPassword(password);
	open_server();
	pollfd.fd = this->getSocketFd();
	pollfd.events = POLLIN;
	pollfds.push_back(pollfd);
}

/* getter setter */
std::string Server::getPassword() const
{
	return this->password;
}

int Server::getPortNum() const
{
	return this->portNum;
}

int Server::getSocketFd() const
{
	return this->socketFd;
}

void Server::setPassword(std::string password)
{
	this->password = password;
}

void Server::setPortNum(int portNum)
{
	this->portNum = portNum;
}

void Server::setSocketFd(int fd)
{
	this->socketFd = fd;
}

void Server::acceptClient() {
	sockaddr_in client;
	socklen_t client_len = sizeof(client);

	int client_fd = accept(this->getSocketFd(), reinterpret_cast<sockaddr *>(&client), &client_len);

	this->users.insert(std::make_pair(client_fd, UserInfo()));
	this->users[client_fd].setFd(client_fd);
	pollfd newone;
	newone.fd = client_fd;
	newone.events = POLLIN;
	this->pollfds.push_back(newone);
	std::cout << "fd: " << client_fd << std::endl;
}

/* command 파싱 및 명령어 실행 */
Command Server::createCommand(std::string cmd, int client_fd)
{
	Command command(client_fd, cmd);

	command.splitCommand();
	return command;
	// std::cout << " check command complete!\n";
}

void Server::executeCommand(Command cmd)
{
	std::cout << "command fd: " << cmd.getFd() << "\n";
	UserInfo &user = this->getUserInfoByFd(cmd.getFd());

	if (cmd.getCommand() == "PASS")
	{
		cmd.command_pass(*this, user);
	}
	else if (cmd.getCommand() == "NICK")
	{
		cmd.commandNick(*this, user);
	}
	else if (cmd.getCommand() == "USER")
	{
		cmd.commandUser();
	}
}

/* fd를 이용해서 IserInfo 레퍼런스 반환 */
UserInfo &Server::getUserInfoByFd(int client_fd)
{
	std::map<int, UserInfo>::iterator it = this->users.find(client_fd);
	std::cout << "find user: " << it->first << "\n";
	if (it != users.end())
	{
		std::cout << it->first << "\n";
		return it->second;
	}
	else
	{
		throw std::runtime_error("Error: Not find any user");
	}
	return it->second;
}
