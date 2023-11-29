#include "Privmsg.hpp"

Privmsg::Privmsg(Message *msg, UserInfo &user, std::map<int, UserInfo> users, std::map<std::string, Channel> channels) : Command(msg), user(user), users(users) channels(channels){}

Privmsg::~Privmsg() {}

void Privmsg::execute()
{
	std::vector<std::string> parameters = getParameters();
	
	if (!parameters[0])
	{
		send (ERR_NORECIPIENT);
		return ;
	}
	if (trailing == "")
	{
		send (ERR_NOTEXTTOSEND);
		return ;
	}
	checkParameters(parameters[0]);
	sendText();
}

void checkParameters(std::string parameter)
{
	if (parameter.find(',') != std::npos)
		splitParameter(parameter);
	else 
		recipients[0] = parameter;
	 
	for (int i = 0; recipients[i]; i++)
		saveRecipient(recipients[i]);

	
	else if (parameter.find('#', 0) != std::npos)
	{
		if (checkChannels())
			return ;
			recipientChannels = checkChannels();
	}
	else
		recipientUsers = checkOtherUsers();
}

void splitParameter(std::string parameter)
{
	parameter()
}

void saveRecipient(std::string recipients[i])
{

}

void checkChannels()
void checkOtherUsers()