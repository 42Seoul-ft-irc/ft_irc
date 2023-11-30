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