#include "Topic.hpp"

Topic::Topic(Message *msg, UserInfo &user,
			 std::map<std::string, Channel> channelList) : Command(msg), user(user), channelList(channelList)
{
}

Topic::~Topic() {}

void Topic::execute()
{
	if (isError())
		return;

	if (getTrailing().empty()) // topic 조회
	{
		std::string channelName = getParameters()[0];
		std::map<std::string, Channel>::iterator it = channelList.find(channelName);

		Channel channel = it->second;

		if (channel.getTopic().empty())
		{
			std::string str = "331 " + channelName + " :No topic is set";
			const char *reply = str.c_str();

			ft_send(user.getFd(), const_cast<char *>(reply));
		}
		else
		{
			std::string str = "332 " + channelName + " :" + channel.getTopic();
			const char *reply = str.c_str();

			ft_send(user.getFd(), const_cast<char *>(reply));
		}
	}
}

bool Topic::isError()
{
	if (!user.getActive())
		return true;

	if (!getParameters().size()) // 461 ERR_NEEDMOREPARAMS
	{
		ft_send(user.getFd(), const_cast<char *>("461 TOPIC :Not enough parameters"));
		return true;
	}

	std::map<std::string, Channel>::iterator it = channelList.find(getParameters()[0]);
	if (it == channelList.end()) // 403 ERR_NOSUCHCHANNEL
	{
		std::string str = "461 ";
		str.append(getParameters()[0]);
		str.append(" :No such channel");

		ft_send(user.getFd(), const_cast<char *>(str.c_str()));
		return true;
	}

	return false;
}
