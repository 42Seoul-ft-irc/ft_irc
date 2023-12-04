#ifndef AUTH_HPP
#define AUTH_HPP

#include "UserInfo.hpp"
#include "utils.hpp"
#include <sstream>

class Auth
{
private:
	UserInfo &user;
	std::map<int, UserInfo> &users;

	std::string serverName;
	bool isNamesEmpty();
	bool isAllPass();
	void sendReplies();
	int isInuseNick();

public:
	Auth(UserInfo &, std::map<int, UserInfo> &, std::string);
};

#endif