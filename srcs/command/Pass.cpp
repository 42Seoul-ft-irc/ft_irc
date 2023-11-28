#include "Pass.hpp"

Pass::Pass(Message *msg, UserInfo &user, std::string password) : Command(msg), user(user), password(password) {}

Pass::~Pass() {}

void Pass::execute()
{
	std::cout << "pass 명령어 실행\n";

	if (getParameters().size() < 2)
	{
		// send(ERR_NEEDMOREPARAMS)
		return;
	}
	else if (getParameters().size() != 2)
	{
		// send(PASS uses 'PASS passparameter')
		return;
	}
	if (user.getPass())
	{
		// send(ERR_ALREADYREGISTRED)
		return;
	}
	if (*getParametersBegin()++ == password)
	{
		user.checkPass();
		std::cout << "password completed\n";
	}
	else
	{
		// send(ERR_PASSWDMISMATCH)
	}

	std::cout << user;
}
