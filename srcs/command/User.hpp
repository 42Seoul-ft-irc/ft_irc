#ifndef USER_HPP
#define USER_HPP

#include "Command.hpp"
#include "../utils.hpp"
#include "../UserInfo.hpp"

class User : public Command {
private:
	UserInfo &user;

public:
	User(Message *, UserInfo &);
	~User();

	void execute();
};

#endif