#include "User.hpp"

User::User(Message *msg, UserInfo &user) : Command(msg), user(user) {}

User::~User() {}

void User::execute()
{
	if (user.getActive() || !user.getPass())
		return;

	if (user.getActive())
	{
		std::string reply = "462 USER :You may not reregister";

		ft_send(user.getFd(), reply); // ERR_ALREADYREGISTRED
		return;
	}
	if (getParameters().size() < 3 || getTrailing().empty())
	{
		std::string reply = "461 USER :You may not reregister";

		ft_send(user.getFd(), reply); // ERR_NEEDMOREPARAMS
		return;
	}

	user.setUsername(getParameters()[0]);
	user.setHostname(getParameters()[1]);
	user.setServername(getParameters()[2]);
	user.setRealname(getTrailing());

	user.checkUser();
}
