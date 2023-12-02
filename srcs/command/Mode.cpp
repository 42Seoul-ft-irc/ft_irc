#include "Mode.hpp"

Mode::Mode(Message *msg, UserInfo &user, std::map<std::string, Channel> &channelList, std::string serverName) : Command(msg), user(user), channelList(channelList), serverName(serverName) {}

Mode::~Mode() {}

void Mode::execute()
{
	if (!user.getActive())
		return;

	if (!getParameters().size())
		return;

	if (!isValidChannelName())
		return;

	if (getParameters().size() == 1) // 324 RPL_CHANNELMODEIS
	{
		std::map<std::string, Channel>::iterator it = channelList.find(getParameters()[0]);

		this->channel = &(it->second);

		std::string modestring = getModestring();
		std::string reply = ":" + serverName + " 324 " + user.getNickname() + " " + getParameters()[0] + " " + modestring;

		ft_send(user.getFd(), reply);
	}

	if (getParameters()[1][0] != '+' && getParameters()[1][0] != '-')
		return;

	if (!isOperator())
		return;
}

bool Mode::isValidChannelName()
{
	std::string channelName = getParameters()[0];

	if (channelName[0] != '#') // 401 ERR_NOSUCHNICK
	{
		std::string reply = ":" + serverName + " 401 " + user.getNickname() + " " + channelName + " :No such nick";

		ft_send(user.getFd(), reply);

		return false;
	}
	else // 403 ERR_NOSUCHCHANNEL
	{
		std::map<std::string, Channel>::iterator it = channelList.find(channelName);

		if (it == channelList.end())
		{
			std::string reply = ":" + serverName + " 403 " + user.getNickname() + " " + channelName + " :No such channel";

			ft_send(user.getFd(), reply);

			return false;
		}
	}
	return true;
}

std::string Mode::getModestring()
{
	std::string modestring = "+";

	bool keyFlag = false;
	bool limitFlag = false;

	if (channel->getInviteMode())
		modestring += "i";
	if (channel->getKeyMode())
	{
		modestring += "k";
		keyFlag = true;
	}
	if (channel->getLimitMode())
	{
		modestring += "l";
		limitFlag = true;
	}
	if (channel->getTopicMode())
		modestring += "t";

	if (keyFlag)
		modestring = modestring + " " + channel->getKey();
	if (limitFlag)
	{
		std::stringstream ss;
		ss << channel->getLimit();
		std::string limit = ss.str();

		modestring = modestring + " :" + limit;
	}

	return modestring;
}

bool Mode::isOperator()
{
	std::map<std::string, UserInfo>::iterator it = channel->operators.find(user.getNickname());

	if (it == channel->operators.end()) // 482 ERR_CHANOPRIVSNEEDED
	{
		std::string reply = ":" + serverName + " 482 " + user.getNickname() + " " + channel->getName() + " :You're not channel operator";

		ft_send(user.getFd(), reply);

		return false;
	}
	return true;
}
