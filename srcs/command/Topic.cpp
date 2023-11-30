#include "Topic.hpp"

Topic::Topic(Message *msg, UserInfo &user, std::map<std::string, Channel> &channelList) : Command(msg), user(user), channelList(channelList) {}

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
		ft_send(user.getFd(), "461 TOPIC :Not enough parameters");

		return true;
	}

	std::map<std::string, Channel>::iterator it = channelList.find(getParameters()[0]);
	if (it == channelList.end()) // 403 ERR_NOSUCHCHANNEL
	{
		std::string reply = "461 " + getParameters()[0] + " :No such channel";

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
		std::string reply = "331 " + channelName + " :No topic is set";

		ft_send(user.getFd(), reply);
	}
	else
	{
		std::string reply = "332 " + channelName + " :" + channel.getTopic();

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
		if (userIt->second || !channel.getTopicMode())
			channel.setTopic(getTrailing());
		else
		{
			std::string reply = "482 " + channelName + " :You're not channel operator";

			ft_send(user.getFd(), reply);
		}
	}
	else
	{
		std::string reply = "442 " + channelName + " :You're not on that channel";

		ft_send(user.getFd(), reply);
	}
}
