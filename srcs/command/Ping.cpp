#include "Ping.hpp"

Ping::Ping(Message *msg, UserInfo &user) : Command(msg), user(user) {}

void Ping::execute()
{
	std::string reply = ":" + user.getHostname() + " PONG " + getParameters()[0];

	ft_send(user.getFd(), reply);
}