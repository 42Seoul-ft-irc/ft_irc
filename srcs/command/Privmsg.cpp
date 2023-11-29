#include "Privmsg.hpp"

Privmsg::Privmsg(Message *msg, UserInfo &user, std::map<int, UserInfo> users, std::map<std::string, Channel> channels) : Command(msg), user(user), users(users) channels(channels){}

Privmsg::~Privmsg() {}

void Privmsg::execute()
{
	std::vector<std::string> parameters = getParameters();
	
	if (!parameters[0])
	{
		//send (ERR_NORECIPIENT);
		return ;
	}
	if (trailing == "")
	{
		//send (ERR_NOTEXTTOSEND);
		return ;
	}
	if (checkParameters(parameters[0]))
		return ;
	sendText();
}

int Privmsg::checkParameters(std::string parameter)
{
	splitParameter(parameter);
	for (int i = 0; recipients[i]; i++)
	{
		if (checkRecipient(recipients[i]))
			return 1;
	}
	if (recipientChannels.size() == 0 && recipientUsersFd.size() == 0)
	{
		//send (ERR_NORECIPIENT);
		return 1;
	}
	//중복 확인
	//if ()
	return 0;
}

void Privmsg::splitParameter(std::string parameter)
{
	int commaPos;

	commaPos = parameter.find(',');
	if (commaPos == std::npos)
	{
		recipients.push_back(parameter);
		return ;
	}
	while (commaPos != std::npos)
	{
		recipients.push_back(parameter.substr(0, commaPos - 1));
		if (!parameter[commaPos + 1] || parameter[commaPos + 1] == ",")
			return ;
		parameter = parameter.substr(commaPos + 1);
		commaPos = parameter.find(',');
	}
	recipients.push_back(parameter.substr(0, commaPos - 1));
}

int Privmsg::checkRecipient(std::string recipient)
{
	if (recipient.find('#', 0) != std::npos)
	{
		if (checkChannels(recipient))
		{
			//send(ERR_CANNOTSENDTOCHAN);
			return 1;
		}
		recipientChannels.push_back(recipient);
	}
	else
	{
		int userFd = checkUsers(recipient);
		if (userFd < 0)
		{
			//send (ERR_NOSUCHNICK);
			return 1;
		}
		recipientUsersFd.push_back(userFd);
	}
}

int Privmsg::checkChannels(std::string recipient)
{
	std::map<std::string, Channel> iter;
	class Channel = NULL;

	for (iter = channels.begin(); iter != channels.end(); iter++)
	{
		if ((*iter).second.getName() == recipient)
			Channel = (*iter).second;
	}
	if (!Channel)
		return 1;
	//전송할 채널에 발신자가 있는지 확인
	// for (iter = channels.begin(); iter != channels.end(); iter++)
	// {
	// 	if ((*iter).second.getName() == recipient)
	// 		Channel = (*iter).second;
	// }
}

int Privmsg::checkUsers(std::string recipient)
{
	std::map<int, UserInfo>::iterator iter;

	for (iter = users.begin(); iter != users.end(); iter++)
	{
		if ((*iter).second.getNickname() == recipient)
			return (*iter).second.getFd();
	}
	return -1;
}