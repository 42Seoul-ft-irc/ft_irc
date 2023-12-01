#ifndef PASS_HPP
#define PASS_HPP

#include "Command.hpp"
#include "../utils.hpp"
#include "../UserInfo.hpp"

class Pass : public Command {
private:
	UserInfo &user;
	std::string password;

public:
	Pass(Message *msg, UserInfo &user, std::string password);
	Pass();
	~Pass();
	void execute();
};

#endif