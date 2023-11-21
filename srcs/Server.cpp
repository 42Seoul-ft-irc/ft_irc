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
Command Server::createCommand(std::string cmd, int client_fd) {
	Command command(client_fd, cmd);
	return command.splitCommand();
	//std::cout << " check command complete!\n";
}

void Server::executeCommand(Command cmd){
	std::cout << "command fd: "<< cmd.getFd()<<"\n";
	UserInfo &user = this->getUserInfoByFd(cmd.getFd());

	if (cmd.getCommand() == "PASS") {
		cmd.command_pass(*this, user);
	}
	else if (cmd.getCommand() == "NICK") {
		//
	}
	else if (cmd.getCommand() == "USER") {
		//
	}
}

/* fd를 이용해서 IserInfo 레퍼런스 반환 */
UserInfo &Server::getUserInfoByFd(int client_fd){
	std::map<int, UserInfo>::iterator it = this->users.find(client_fd);
	std::cout << "find user: " << it->first << "\n";
	if (it != users.end()) {
		std::cout << it->first << "\n";
		return it->second;
	}
	else {
		throw std::runtime_error("Error: Not find any user");
	}
	return it->second;
}