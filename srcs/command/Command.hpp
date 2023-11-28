#ifndef COMMAND_HPP
#define COMMAND_HPP

#include "Message.hpp"
#include <string>
#include <vector>

class Command
{
private:
	int fd;
	std::string originalMessage;
	std::string command;
	std::vector<std::string> parameters;
	std::string trailing;

public:
	Command(Message *msg);
	virtual ~Command();

	virtual void execute()=0;

	// getter
	int getFd() const;
	std::string getOriginalMessage() const;
	std::string getCommand() const;
	std::vector<std::string> getParameters() const;
	std::vector<std::string>::iterator getParametersBegin();
	std::string getTrailing() const;

	// setter
	void setCommand(std::string);
	void setParameters(std::string);
	void setTrailing(std::string);

	// 여기서부터 커맨드 추가
	// void commandPass(Server &server, UserInfo &user);
	// void commandNick(Server &server, UserInfo &user);
	// int checkNicknameForm(Server &server);
	// int checkDuplicateNickname(Server &server);
};

#endif