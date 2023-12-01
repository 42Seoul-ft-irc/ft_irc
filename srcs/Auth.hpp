#ifndef AUTH_HPP
#define AUTH_HPP

#include "UserInfo.hpp"
#include "utils.hpp"

class Auth
{
private:
	UserInfo &user;
	std::string serverName;

	bool isNamesEmpty();
	bool isAllPass();
	void sendReplies();

public:
	Auth(UserInfo &, std::string);
};

#endif