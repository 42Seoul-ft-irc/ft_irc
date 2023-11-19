#include "Server.hpp"

// getter setter
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

//command
/* command 파싱 및 명령어 실행 */
void Server::checkCommand(std::string cmd, int client_fd) {
	Command command(client_fd, cmd);
	//command.user = this->getUserInfoByFd(client_fd);

	if (cmd == "PASS") {
		command.command_pass();
	}
	else if (cmd == "NICK") {
		//
	}
	else if (cmd == "USER") {
		//
	}
}

/* fd를 이용해서 IserInfo 레퍼런스 반환 */
UserInfo &Server::getUserInfoByFd(int client_fd){
	std::map<int, UserInfo>::iterator it = this->users.find(client_fd);
	if (it == users.end()) {
		throw std::runtime_error("Error: Not find any user");
	}
	return it->second;
}