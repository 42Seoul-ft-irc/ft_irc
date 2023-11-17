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
