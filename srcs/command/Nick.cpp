#include "Nick.hpp"

Nick::Nick(Message *msg, UserInfo &user, std::map<int, UserInfo> users) : Command(msg), user(user), users(users) {}

Nick::~Nick() {}

void Nick::execute()
{
	if (!user.getPass())
		return;
	if (getParameters().size() < 1)
	{
		std::string reply = ":" + user.getHostname() + " 431 " + user.getNickname() + " :No nickname given";
		ft_send(user.getFd(), reply); 
		return;
	}
	if (user.getNick()) // 원래 유저 닉네임 변경
	{
		if (!checkNicknameForm())
		{
			user.setNickname(getParameters().at(0));
			std::cout << "nickname update completed\n";
		}
	}
	else // 새 유저 닉네임 생성
	{
		if (!checkNicknameForm())
		{
			user.checkNick();
			user.setNickname(getParameters().at(0));
			std::cout << "nickname completed\n";
		}
	}
}

int Nick::checkNicknameForm()
{
	if (getParameters()[0].size() >= 10)
	{
		// send(ERR_ERRONEUSNICKNAME)
		std::string msg = ":" + user.getHostname() + "432 " + getParameters().at(0) + " :Erroneus nickname";
		ft_send(user.getFd(), msg);
		return 1;
	}
	return 0;
}
