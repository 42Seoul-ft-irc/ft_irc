#ifndef NICK_HPP
#define NICK_HPP

#include "Command.hpp"
#include "../UserInfo.hpp"
#include "../utils.hpp"
#include <map>

class Nick : public Command
{
private:
	UserInfo &user;
	std::map<int, UserInfo> users;

	int checkNicknameForm();

public:
	Nick(Message *msg, UserInfo &user, std::map<int, UserInfo> users);
	~Nick();

	void execute();
};

#endif