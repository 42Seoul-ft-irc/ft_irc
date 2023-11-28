#include "User.hpp"

User::User(Message *msg, UserInfo &user) : Command(msg), user(user) {}

User::~User() {}

void User::execute()
{
	if (!user.getPass())
		return;

	if (user.getActive())
		ft_send(user.getFd(), "462 :You may not reregister"); // ERR_ALREADYREGISTRED

	if (getParameters().size() < 3)
		ft_send(user.getFd(), "461 USER :Not enough parameters"); // ERR_NEEDMOREPARAMS

	if (getTrailing().empty())
		ft_send(user.getFd(), "461 USER :Not enough parameters"); // ERR_NEEDMOREPARAMS

	user.setUsername(getParameters()[0]);
	user.setHostname(getParameters()[1]);
	user.setServername(getParameters()[2]);
	user.setRealname(getTrailing());

	user.checkUser();
}
