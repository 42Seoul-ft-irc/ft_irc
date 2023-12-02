#ifndef PING_HPP
#define PING_HPP

#include "Command.hpp"
#include "../UserInfo.hpp"
#include "../utils.hpp"

class Ping : public Command
{
private:
	UserInfo &user;

public:
	Ping(Message *, UserInfo &);
	void execute();
};

#endif