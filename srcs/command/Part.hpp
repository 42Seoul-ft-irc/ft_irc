#ifndef PART_HPP
#define PART_HPP

#include "Command.hpp"
#include "../utils.hpp"
#include "../UserInfo.hpp"
#include "../Message.hpp"
#include "../Channel.hpp"

class Part : public Command
{
private:
	UserInfo &user;
	std::map<int, UserInfo> *users;
	std::map<std::string, Channel> *channels;

	Channel *PartChannel;
    std::vector<std::string> partChannelName;

public:
	Part(Message *msg, UserInfo &user, std::map<int, UserInfo> *users, std::map<std::string, Channel> *channels);
	~Part();

	void execute();
	void splitParameter(std::string parameter);
	int isChannel(std::string partChannelName);

	void partUsers();
	int checkUsers(std::string partChannelName);
	int checkChannel(std::string parameter);

	int eraseChannelInUserInfo(std::string partChannelName);
	void eraseUserInChannel(Channel *channel, std::string partChannelName);
	void eraseUser(std::string partChannelName);
};

void ft_send(int fd, std::string str);

#endif