#include "Pass.hpp"

Pass::Pass(Message *msg, UserInfo &user, std::string password) : Command(msg), user(user), password(password) {}

Pass::~Pass() {}

void Pass::execute()
{
	std::cout << "pass 명령어 실행\n";

	if (getParameters().size() < 1)
	{
		std::string msg = "461 PASS :Not enough parameters";
		ft_send(user.getFd(), msg);
		return;
	}
	if (user.getActive() == true)
	{
		std::string msg = "462 :You may not reregister";
		ft_send(user.getFd(), msg);
		return;
	}
	if (*getParametersBegin()++ == password)
	{
		user.checkPass();
		std::cout << "password completed\n";
	}
	else
	{
		std::string msg = "464 :Password incorrect";
		ft_send(user.getFd(), msg);
		return;
	}
}
