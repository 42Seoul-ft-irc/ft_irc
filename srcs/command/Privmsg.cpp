#include "Privmsg.hpp"

Privmsg::Privmsg(Message *msg, UserInfo &user, std::map<int, UserInfo> users, std::map<std::string, Channel> channels) : Command(msg), user(user), users(users), channels(channels){}

Privmsg::~Privmsg() {}

void Privmsg::execute()
{
	std::vector<std::string> parameters = getParameters();
	
	if (parameters.empty())
	{
		//send (ERR_NORECIPIENT);
		return ;
	}
	if (getTrailing() == "")
	{
		//send (ERR_NOTEXTTOSEND);
		return ;
	}
	if (checkParameters(parameters[0]))
		return ;
	//채널의 사용자들로 전송
	if (recipientChannels.size() > 0)
	{
		for (size_t i = 0; i < recipientChannels.size(); i++)
		{
			sendUsersOfChannel(recipientChannels[i]);
		}

	}
	//사용자들로 전송
	if (recipientUsersFd.size() > 0)
	{
		for (size_t i = 0; i < recipientUsersFd.size(); i++)
		{
			ft_send(recipientUsersFd[i], getTrailing());
		}
	}
}

void Privmsg::sendUsersOfChannel(Channel channel)
{
	std::map<std::string, UserInfo>::iterator iterUsers;

	for (iterUsers = channel.users.begin(); iterUsers != channel.users.end(); iterUsers++)
	{
		ft_send((*iterUsers).second.getFd(), getTrailing());
	}
}

int Privmsg::checkParameters(std::string parameter)
{
	splitParameter(parameter);
	for (size_t i = 0; recipients.size(); i++)
	{
		if (checkRecipient(recipients[i]))
			return 1;
	}
	if (recipientChannels.size() == 0 && recipientUsersFd.size() == 0)
	{
		//send (ERR_NORECIPIENT);
		return 1;
	}
	return 0;
}

void Privmsg::splitParameter(std::string parameter)
{
	size_t commaPos;

	commaPos = parameter.find(',');
	if (commaPos == std::string::npos)
	{
		recipients.push_back(parameter);
		return ;
	}
	while (commaPos != std::string::npos)
	{
		recipients.push_back(parameter.substr(0, commaPos - 1));
		if (!parameter[commaPos + 1] || parameter[commaPos + 1] == ',')
			return ;
		parameter = parameter.substr(commaPos + 1);
		commaPos = parameter.find(',');
	}
	recipients.push_back(parameter.substr(0, commaPos - 1));
}

int Privmsg::checkRecipient(std::string recipient)
{
	if (recipient.find('#', 0) != std::string::npos)
	{
		if (checkChannels(recipient))
		{
			//send(ERR_CANNOTSENDTOCHAN);
			return 1;
		}
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
	return 0;
}

int Privmsg::checkChannels(std::string recipient)
{
	std::map<std::string, Channel>::iterator iter;
	std::map<std::string, UserInfo>::iterator iterUsers;
	Channel recipientChannel(user, "");
	bool isChannel = false;

	for (iter = channels.begin(); iter != channels.end(); iter++)
	{
		if ((*iter).second.getName() == recipient)
		{
			recipientChannel = (*iter).second;
			isChannel = true;
		}
	}
	if (isChannel == false)
		return 1;
	//전송할 채널에 발신자가 있는지 확인
	for (iterUsers = recipientChannel.users.begin(); iterUsers != recipientChannel.users.end(); iterUsers++)
	{
		if ((*iterUsers).first == this->user.getNickname())
		{
			recipientChannels.push_back(recipientChannel);
			return 0;
		}
	}
	return 1;
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