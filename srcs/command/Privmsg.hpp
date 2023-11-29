#ifndef PRIVMSG_HPP
#define PRIVMSG_HPP

#include "Command.hpp"
#include "UserInfo.hpp"
#include "Channel.hpp"
#include <map>
#include <vector>

class Privmsg : public Command
{
private:
	UserInfo &user;
	std::map<int, UserInfo> users;
	std::map<std::string, Channel> channels;

	std::vector<std::string> recipients;
	std::vector<std::string> recipientChannels;
	std::vector<int> recipientUsersFd;
	

public:
	Privmsg(Message *msg, UserInfo &user, std::map<int, UserInfo> users, std::map<std::string, Channel> channels);
	~Privmsg();

	void execute();
	int checkParameters(std::string parameter);
	void splitParameter(std::string parameter);

	int checkRecipient(std::string recipient);
	int checkChannels(std::string recipient);
	int checkUsers(std::string recipient);

};

#endif