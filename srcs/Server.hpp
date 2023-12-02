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
#include <csignal>
#include "UserInfo.hpp"
#include "Channel.hpp"
#include "command/Command.hpp"
#include "Message.hpp"
#include "command/Pass.hpp"
#include "command/Nick.hpp"
#include "command/User.hpp"
#include "command/Join.hpp"
#include "command/Invite.hpp"
#include "Auth.hpp"
#include "command/Topic.hpp"
#include "command/Privmsg.hpp"
#include "command/Quit.hpp"

class UserInfo;
class Command;
class Channel;

class Server
{

private:
	int portNum;
	std::string password;
	int socketFd;
	std::string serverName;

	int convertPort(char *portStr);
	void openServer();
	void createSocket();
	void setServerAddr(struct sockaddr_in &serverAddr, int portNum);
	void pushServerPollfd();

public:
	std::map<int, UserInfo> users;
	std::map<std::string, Channel> channels;
	char clientBuffer[SOMAXCONN][BUFSIZ];
	std::vector<pollfd> pollfds;

	Server(int argc, char **argv);

	int getPortNum() const;
	std::string getPassword() const;
	int getSocketFd() const;
	std::string getServerName() const;

	void setPortNum(int portNum);
	void setPassword(std::string password);
	void setSocketFd(int fd);

	void acceptClient();
	Command *createCommand(UserInfo &user, std::string recvStr);
	void executeCommand(Command *cmd, UserInfo &user);

	UserInfo &getUserInfoByFd(int userFd);
};

#endif