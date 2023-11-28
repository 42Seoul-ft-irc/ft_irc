#include "Server.hpp"

/* 생성자 */
static int convertPort(char *portStr)
{
	for (size_t i = 0; i < strlen(portStr); i++)
		if (!isdigit(portStr[i]))
			throw std::invalid_argument("Error: invalid argument");

	int port = atoi(portStr);

	if (port < 0 || 65535 < port)
		throw std::invalid_argument("Error: invalid argument");

	return port;
}

void Server::createSocket()
{
	int socketFd = socket(AF_INET, SOCK_STREAM, 0);

	if (socketFd == -1)
		throw std::runtime_error("socket error");

	setSocketFd(socketFd);
}

void setServerAddr(struct sockaddr_in &serverAddr, int portNum)
{
	std::memset(&serverAddr, 0, sizeof(serverAddr));

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAddr.sin_port = htons(portNum);
}

void Server::openServer()
{
	createSocket();

	try
	{
		// 소켓 포트 연결
		struct sockaddr_in serverAddr;
		setServerAddr(serverAddr, getPortNum());

		if (bind(getSocketFd(), reinterpret_cast<const struct sockaddr *>(&serverAddr), sizeof(serverAddr)) == -1)
			throw std::runtime_error("Error: bind error");

		if (listen(getSocketFd(), SOMAXCONN) == -1)
			throw std::runtime_error("Error: listen error");
	}
	catch (const std::exception &e)
	{
		close(getSocketFd());

		throw std::runtime_error(e.what());
	}
}

void Server::pushServerPollfd()
{
	pollfd pollfd;

	pollfd.fd = getSocketFd();
	pollfd.events = POLLIN;
	pollfds.push_back(pollfd);
}

Server::Server(int argc, char **argv)
{
	if (argc != 3)
		throw std::invalid_argument("Error: invalid argument");

	setPortNum(convertPort(argv[1]));
	std::string password(argv[2]);
	setPassword(password);

	openServer();
	pushServerPollfd();
}

Server::Server() {}

/* getter setter */
std::string Server::getPassword() const
{
	return password;
}

int Server::getPortNum() const
{
	return portNum;
}

int Server::getSocketFd() const
{
	return socketFd;
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

void Server::acceptClient()
{
	sockaddr_in client;
	socklen_t clientLen = sizeof(client);

	int clientFd = accept(getSocketFd(), reinterpret_cast<sockaddr *>(&client), &clientLen);

	users.insert(std::make_pair(clientFd, UserInfo()));
	users[clientFd].setFd(clientFd);

	pollfd newPollfd;
	newPollfd.fd = clientFd;
	newPollfd.events = POLLIN;
	pollfds.push_back(newPollfd);

	std::cout << "new client fd: " << clientFd << std::endl;
}

/* command 파싱 및 명령어 실행 */
Command *Server::createCommand(int fd, std::string recvStr)
{
	Message msg(fd, recvStr);
	
	UserInfo &user = getUserInfoByFd(msg.getFd());

	std::cout << user;
	std::cout << msg << std::endl;

	Command *cmd = 0;

	if (msg.getCommand() == "PASS")
	{
		cmd = new Pass(&msg, user, password);
	}
	else if (msg.getCommand() == "NICK")
	{
		cmd = new Nick(&msg, user, users);
	}
	else if (msg.getCommand() == "USER")
	{

	}
	else if (msg.getCommand() == "JOIN")
	{
		cmd = new Join(&msg, user, &this->channels);
	}

	return cmd;
}

void Server::executeCommand(Command *cmd)
{
	if (cmd)
	{
		cmd->execute();
		delete (cmd);
	}
}

/* fd를 이용해서 IserInfo 레퍼런스 반환 */
UserInfo &Server::getUserInfoByFd(int clientFd)
{
	std::map<int, UserInfo>::iterator it = users.find(clientFd);
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
