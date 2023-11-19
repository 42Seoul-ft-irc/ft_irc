#include "Server.hpp"

// getter
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


// setter
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


void Server::checkCommand(std::string cmd, int client_fd) {
	Command command(client_fd, cmd);
	UserInfo &client = this->getUserInfo(client_fd);
	if (cmd == "PASS") {
		command.pass(client);
	}
	else if (cmd == "NICK") {

	}
	else if (cmd == "USER") {

	}
}

UserInfo &Server::getUserInfo(int client_fd){
	std::map<int, UserInfo>::iterator it = this->users.find(client_fd);
	if (it == users.end()) {
		throw std::runtime_error("Error: Not find any user");
	}
	return it->second;
}