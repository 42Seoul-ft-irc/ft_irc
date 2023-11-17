#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "Server.hpp"

class Channel
{
private:
	std::string name;
	std::map<std::string, UserInfo&> operators;
	std::map<std::string, UserInfo&> users;
	char mode;

public:
	Channel();
	~Channel();
};

Channel::Channel()
{
}

Channel::~Channel()
{
}


#endif