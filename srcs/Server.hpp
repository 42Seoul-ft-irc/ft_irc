#ifndef SERVER_HPP
#define SERVER_HPP

#include <string>
#include <sstream>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <exception>
#include <cstdlib>
#include <poll.h>
#include <unistd.h>
#include <vector>
#include <map>
#include "UserInfo.hpp"
//#include "Channel.hpp"
#include "Command.hpp"

class UserInfo;
class Command;

class Server
{
private:
	int portNum;
	std::string password;
	int socketFd;
	//int numOfClient;

public:
	int getPortNum() const;
	std::string getPassword() const;
	int getSocketFd() const;
	//int getNumOfClient() const;

	void setPortNum(int portNum);
	void setPassword(std::string password);
	void setSocketFd(int fd);
	//void setNumOfClient(int numOfClient);
	Command createCommand(std::string cmd, int client_fd);
	void executeCommand(Command command);

	// 특정 fd의 UserInfo 찾음
	UserInfo &getUserInfoByFd(int userFd);

	std::map<int, UserInfo> users;
};

void argv_parsing(int argc, char **argv, Server &server);
void open_server(Server &server);
void create_socket(Server &server);

#endif