#ifndef USER_HPP
#define USER_HPP

#include "Command.hpp"
#include "../utils.hpp"
#include "../UserInfo.hpp"

class User : public Command {
private:
	UserInfo &user;
	std::string serverName;

public:
	User(Message *, UserInfo &, std::string);
	~User();
	void execute();
};

#endif