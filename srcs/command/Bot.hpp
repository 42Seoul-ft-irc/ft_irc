#pragma once

#include <cmath>
#include "Command.hpp"
#include "../Server.hpp"
#include "../UserInfo.hpp"
#include "../utils.hpp"

class UserInfo;

class Bot : public Command
{
private:
	UserInfo &user;
	std::string recommendDinnerMenu();

public:
	Bot(Message *msg, UserInfo &user);
	void execute();
};