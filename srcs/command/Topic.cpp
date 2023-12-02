#include "Topic.hpp"

Topic::Topic(Message *msg, UserInfo &user, std::map<std::string, Channel> &channelList, std::string serverName) : Command(msg), user(user), channelList(channelList), serverName(serverName) {}

Topic::~Topic() {}

void Topic::execute()
{
	if (!user.getActive())
		return;

	if (isError())
		return;

	std::string channelName = getParameters()[0];

	if (getTrailing().empty())
		checkTopic(channelName);
	else
		editTopic(channelName);
}

bool Topic::isError()
{
	if (!user.getActive())
		return true;

	if (!getParameters().size()) // 461 ERR_NEEDMOREPARAMS
	{
		std::string reply = ":" + serverName + " 461 " + user.getNickname() + " TOPIC :Not enough parameters";

		ft_send(user.getFd(), reply);

		return true;
	}

	std::map<std::string, Channel>::iterator it = channelList.find(getParameters()[0]);
	if (it == channelList.end()) // 403 ERR_NOSUCHCHANNEL
	{
		std::string reply = ":" + serverName + " 403 " + user.getNickname() + " " + getParameters()[0] + " :No such channel";

		ft_send(user.getFd(), reply);

		return true;
	}

	return false;
}

void Topic::checkTopic(std::string channelName)
{
	std::map<std::string, Channel>::iterator it = channelList.find(channelName);

	Channel channel = it->second;

	if (channel.getTopic().empty())
	{
		std::string reply = ":" + serverName + " 331 " + user.getNickname() + " " + getParameters()[0] + " :No topic is set";

		ft_send(user.getFd(), reply);
	}
	else
	{
		std::string reply = ":" + serverName + " 332 " + user.getNickname() + " " + getParameters()[0] + " :" + channel.getTopic();

		ft_send(user.getFd(), reply);
	}
}

void Topic::editTopic(std::string channelName)
{
	std::map<std::string, bool>::iterator userIt = user.channels.find(channelName);
	std::map<std::string, Channel>::iterator channelIt = channelList.find(channelName);
	Channel &channel = channelIt->second;

	if (userIt != user.channels.end())
	{
		if (getTrailing() == channel.getTopic())
			return;

		if (userIt->second || !channel.getTopicMode())
		{
			channel.setTopic(getTrailing());

			std::map<std::string, UserInfo>::iterator it = channel.users.begin();

			for (; it != channel.users.end(); ++it)
			{
				UserInfo userInfo = it->second;

				std::string reply = ":" + userInfo.getNickname() + "!" + userInfo.getUsername() + "@" + user.getHostname() + " TOPIC " + channelName + " :" + getTrailing();

				ft_send(userInfo.getFd(), reply);
			}
		}
		else
		{
			std::string reply = ":" + serverName + " 482 " + user.getNickname() + " " + getParameters()[0] + " :You do not have access to change the topic on this channel";

			ft_send(user.getFd(), reply);
		}
	}
	else
	{
		std::string reply = ":" + serverName + " 442 " + user.getNickname() + " " + getParameters()[0] + " :You're not on that channel";

		ft_send(user.getFd(), reply);
	}
}
