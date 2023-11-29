#ifndef PRIVMSG_HPP
#define PRIVMSG_HPP

#include "Command.hpp"
#include "UserInfo.hpp"
#include "Channel.hpp"
#include <map>

class Privmsg : public Command
{
private:
	UserInfo &user;
	std::map<int, UserInfo> users;
	std::map<std::string, Channel> channels;

	std::vector<std::string> recipients;
	std::vector<std::string> recipientChannels;
	std::vector<int> recipientUsers;
	

public:
	Privmsg(Message *msg, UserInfo &user, std::map<int, UserInfo> users, std::map<std::string, Channel> channels);
	~Privmsg();

	void execute();
};

#endif