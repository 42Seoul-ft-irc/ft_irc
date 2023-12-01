#include "Nick.hpp"

Nick::Nick(Message *msg, UserInfo &user, std::map<int, UserInfo> users) : Command(msg), user(user), users(users) {}

Nick::~Nick() {}

void Nick::execute()
{
	if (getParameters().size() < 2)
	{
		// send(ERR_NEEDMOREPARAMS)
	}
	else if (getParameters().size() != 2)
	{
		// send(NICK uses 'NICK passparameter')
	}
	if (user.getNick()) // 원래 유저 닉네임 변경
	{
		if (!checkNicknameForm())
			std::cout << "nickname update completed\n";
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

int Nick::checkDuplicateNickname()
{
	std::map<int, UserInfo>::iterator iter;

	for (iter = users.begin(); iter != users.end(); iter++)
	{
		if ((*iter).second.getNickname() == getParameters()[0])
			return 1;
	}
	return 0;
}

int Nick::checkNicknameForm()
{
	if (getParameters()[1].size() >= 10)
	{
		// send(ERR_ERRONEUSNICKNAME)
		return 1;
	}
	if (checkDuplicateNickname())
	{
		// send(ERR_NICKNAMEINUSE)
		return 1;
	}
	return 0;
}
