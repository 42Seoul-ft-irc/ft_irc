#include "Nick.hpp"

Nick::Nick(Message *msg, UserInfo &user, std::map<int, UserInfo> users) : Command(msg), user(user), users(users) {}

Nick::~Nick() {}

void Nick::execute()
{
	if (user.getActive() || !user.getPass())
		return;

	if (getParameters().size() < 1)
	{
		std::string reply = "431 :No nickname given";
		ft_send(user.getFd(), reply); 
		return;
	}

	if (!checkNicknameForm())
	{
		user.checkNick();
		user.setNickname(getParameters().at(0));
		std::cout << "nickname completed\n";
	}
}

int Nick::checkNicknameForm()
{
	if (getParameters()[0].size() >= 10)
	{
		// send(ERR_ERRONEUSNICKNAME)
		std::string msg = "432 " + getParameters().at(0) + " :Erroneus nickname";
		ft_send(user.getFd(), msg);
		return 1;
	}
	return 0;
}
