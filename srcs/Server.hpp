#pragma once
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
#include <set>
#include "UserInfo.hpp"
#include "Channel.hpp"
#include "command/Command.hpp"
#include "Message.hpp"
#include "command/Pass.hpp"
#include "command/Nick.hpp"

class UserInfo;
class Command;
class Channel;

class Server
{

private:
	int portNum;
	std::string password;
	int socketFd;

	void pushServerPollfd();
	void createSocket();
	void openServer();

public:
	std::map<int, UserInfo> users;
	std::map<std::string, Channel *> channels;
	char clientBuffer[SOMAXCONN][BUFSIZ];
	std::vector<pollfd> pollfds;

	Server();
	Server(int argc, char **argv);

	int getPortNum() const;
	std::string getPassword() const;
	int getSocketFd() const;

	void setPortNum(int portNum);
	void setPassword(std::string password);
	void setSocketFd(int fd);

	void acceptClient();

	Command *createCommand(int fd, std::string recvStr);
	void executeCommand(Command *cmd);
	// 특정 fd의 UserInfo 찾음
	UserInfo &getUserInfoByFd(int userFd);
};

#endif