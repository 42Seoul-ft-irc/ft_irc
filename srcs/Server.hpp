#ifndef SERVER_HPP
#define SERVER_HPP

#include <string>
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

typedef struct userInfo
{
	std::string nickname;
	std::string username;
	std::string mode;		// todo 숫자? 
	std::string unused;
	std::string realname;
} userInfo;

class Server
{
private:
	int portNum;
	std::string password;
	int socketFd;

public:
	int getPortNum() const;
	std::string getPassword() const;
	int getSocketFd() const;

	void setPortNum(int portNum);
	void setPassword(std::string password);
	void setSocketFd(int fd);
};

void parsing(int argc, char **argv, Server &server);
void open_server(Server &server);
void create_socket(Server &server);

#endif