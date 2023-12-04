#include "User.hpp"

User::User(Message *msg, UserInfo &user) : Command(msg), user(user) {}

User::~User() {}

void User::execute()
{
	if (!user.getPass())
		return;
	if (user.getActive())
	{
		std::string reply = ":" + user.getHostname() + " 462 " + user.getNickname() + " :You may not reregister";

		ft_send(user.getFd(), reply); // ERR_ALREADYREGISTRED
		return;
	}
	if (getParameters().size() < 3 || getTrailing().empty())
	{
		std::string reply = ":" + user.getHostname() + " 461 " + user.getNickname() + " USER :You may not reregister";

		ft_send(user.getFd(), reply); // ERR_NEEDMOREPARAMS
		return;
	}

	user.setUsername(getParameters()[0]);
	user.setHostname(getParameters()[1]);
	user.setServername(getParameters()[2]);
	user.setRealname(getTrailing());

	user.checkUser();
}
