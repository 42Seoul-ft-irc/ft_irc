#ifndef KICK_HPP
#define KICK_HPP

#include "Command.hpp"
#include "../utils.hpp"
#include "../UserInfo.hpp"
#include "../Message.hpp"
#include "../Channel.hpp"

class Kick : public Command
{
private:
	UserInfo &user;
	std::map<int, UserInfo> users;
	std::map<std::string, Channel> channels;

    std::vector<std::string> kickChannelsName;
    std::vector<Channel> kickChannels;

public:
	Kick(Message *msg, UserInfo &user, std::map<int, UserInfo> users, std::map<std::string, Channel> channels);
	~Kick();

	void execute();

};

void ft_send(int fd, std::string str);

#endif