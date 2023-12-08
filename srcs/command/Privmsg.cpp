#include "Privmsg.hpp"

Privmsg::Privmsg(Message *msg, UserInfo &user, std::map<int, UserInfo> users, std::map<std::string, Channel> channels) : Command(msg), user(user), users(users), channels(channels){}

Privmsg::~Privmsg() {}

void Privmsg::sendUsersOfChannel(Channel channel)
{
	std::map<std::string, UserInfo>::iterator iterUsers;

	for (iterUsers = channel.users.begin(); iterUsers != channel.users.end(); iterUsers++)
	{
		std::string msg = ":" + user.getNickname() + "!" + user.getUsername() + "@" + user.getServername() + " PRIVMSG " +  + " " + channel.getName() + " :" + getTrailing();

		if (user.getFd() != (*iterUsers).second.getFd())
			ft_send((*iterUsers).second.getFd(), msg);
	}
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
			break ;
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
		{
			recipientUsers.push_back((*iter).second);
			return 0;
		}
	}
	return 1;
}

int Privmsg::checkRecipient(std::string recipient)
{
	if (recipient.find('#', 0) != std::string::npos)
	{
		if (checkChannels(recipient))
		{
			std::string msg = ":" + user.getHostname() + " 404 " + user.getNickname() + " " + recipient + " :Cannot send to channel";
			ft_send(user.getFd(), msg);
			return 1;
		}
	}
	else
	{
		if (checkUsers(recipient))
		{
			std::string msg = ":" + user.getHostname() + " 401 " + user.getNickname() + " " + recipient + " :No such nick";
			ft_send(user.getFd(), msg);
			return 1;
		}
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
	recipients.push_back(parameter);
}

int Privmsg::checkParameters(std::string parameter)
{
	splitParameter(parameter);

	for (size_t i = 0; i < recipients.size(); i++)
		if (checkRecipient(recipients[i]))
			return 1;

	if (recipientChannels.size() == 0 && recipientUsers.size() == 0)
	{
		std::string msg = ":" + user.getHostname() + " 411 " + user.getNickname() + " :No recipient given";
		ft_send(user.getFd(), msg);
		return 1;
	}
	return 0;
}

void Privmsg::execute()
{
	if (!user.getActive())
		return;
	std::vector<std::string> parameters = getParameters();

	if (parameters.empty() || parameters[0].empty()) // ERR_NORECIPIENT
	{
		std::string msg = ":" + user.getHostname() + " 411 " + user.getNickname() + " :No recipient given";
		ft_send(user.getFd(), msg);
		return ;
	}
	if (getTrailing() == "") // ERR_NOTEXTTOSEND
	{
		std::string msg = ":" + user.getHostname() + " 412 " + user.getNickname() + " :No text to send";
		ft_send(user.getFd(), msg);

		return;
	}

	if (checkParameters(parameters[0]))
		return ;

	if (recipientChannels.size() > 0) // 채널의 사용자들로 전송
		for (size_t i = 0; i < recipientChannels.size(); i++)
			sendUsersOfChannel(recipientChannels[i]);

	if (recipientUsers.size() > 0) // 사용자들로 전송
	{
		for (size_t i = 0; i < recipientUsers.size(); i++)
		{
			std::string msg = ":" + user.getNickname() + "!" + user.getUsername() + "@" + user.getServername() + " PRIVMSG " +  + " " + recipientUsers[i].getNickname() + " :" + getTrailing();

			if (user.getFd() != (recipientUsers[i].getFd()))
				ft_send(recipientUsers[i].getFd(), msg);
		}
	}
}