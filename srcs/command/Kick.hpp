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
	std::map<int, UserInfo> *users;
	std::map<std::string, Channel> *channels;

	Channel *kickChannel;
    std::vector<std::string> kickUsersName;
	UserInfo *kickUser;

public:
	Kick(Message *msg, UserInfo &user, std::map<int, UserInfo> *users, std::map<std::string, Channel> *channels);
	~Kick();

	void execute();
	int checkChannel(std::string parameter);

	int checkOperator(std::string channel);

	void kickUsers(std::string parameter);
	void splitParameter(std::string parameter);
	int checkUsers(std::string channel);

	void eraseUser();
	void eraseChannelInUserInfo(UserInfo *userInfo);
	void eraseUserInChannel(Channel *channel);

};

void ft_send(int fd, std::string str);

#endif