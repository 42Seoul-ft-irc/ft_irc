#include "Mode.hpp"

Mode::Mode(Message *msg, UserInfo &user, std::map<std::string, Channel> &channelList, std::string serverName) : Command(msg), user(user), channelList(channelList), serverName(serverName), paramsIndex(2) {}

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

	if (getParameters()[1].length() < 2)
		return;

	if (getParameters()[1][0] != '+' && getParameters()[1][0] != '-')
		return;

	if (!isOperator())
		return;

	run();
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

void Mode::run()
{
	std::string modestring = getParameters()[1];

	saveInputModes(modestring);
	removeDuplicates();
	executeModes();
}

void Mode::saveInputModes(std::string modestring)
{
	for (size_t i = 0; i < modestring.length(); i++)
	{
		if (modestring[i] == '+')
			sign = "+";
		else if (modestring[i] == '-')
			sign = "-";
		else
		{
			std::string mode = sign + modestring[i];

			inputModes.push_back(mode);
		}
	}
}

void Mode::removeDuplicates()
{
	modes.push_back(inputModes[0]);

	for (size_t i = 1; i < inputModes.size(); i++)
		if (modes.back() != inputModes[i])
			modes.push_back(inputModes[i]);
}

void Mode::executeModes()
{
	for (size_t i = 0; i < modes.size(); i++)
	{
		std::string mode = modes[i];

		switch (mode[1])
		{
		case 'i':
			executeInviteMode(mode);
			break;
		case 'k':
			executeKeyMode(mode);
			break;
		case 'l':
			executeLimitMode(mode);
			break;
		case 'o':
			executeOperatorMode(mode);
			break;
		case 't':
			executeTopicMode(mode);
			break;
		default:

			break;
		}
	}
}

void Mode::executeInviteMode(std::string mode)
{
	if (mode == "+i" && channel->getInviteMode())
		return;
	else if (mode == "-i" && !channel->getInviteMode())
		return;

	changeInviteMode();
	changed.push_back(mode);
}

void Mode::executeKeyMode(std::string mode)
{
	if (paramsIndex > getParameters().size() - 1)
	{
		std::string reply = ":" + serverName + " 696 " + user.getNickname() + " " + channel->getName() + " k * :You must specify a parameter for the key mode. Syntax: <key>.";

		ft_send(user.getFd(), reply);

		return;
	}

	if (!channel->getKeyMode() && mode == "+k")
	{
		channel->setKey(getParameters()[paramsIndex]);
		channel->setKeyMode(true);
		changed.push_back(mode);
		changedParams.push_back(channel->getKey());
	}
	else if (channel->getKeyMode() && mode == "-k")
	{
		if (getParameters()[paramsIndex] == channel->getKey())
		{
			channel->setKeyMode(false);
			changed.push_back(mode);
			changedParams.push_back(channel->getKey());
			channel->setKey("");
		}
		else
		{
			std::string reply = ":" + serverName + " 467 " + user.getNickname() + " " + channel->getName() + " :Channel key already set";

			ft_send(user.getFd(), reply);
		}
	}
	paramsIndex++;
}

void Mode::executeLimitMode(std::string mode)
{
	if (mode == "-l" && channel->getLimitMode())
	{
		channel->setLimit(0);
		channel->setLimitMode(false);
		changed.push_back(mode);

		return;
	}
	else if (mode == " +l")
	{
		if (paramsIndex > getParameters().size() - 1) // 파라미터 없을 때
		{
			std::string reply = ":" + serverName + " 696 " + user.getNickname() + " " + channel->getName() + " l * :You must specify a parameter for the limit mode. Syntax: <limit>.";

			ft_send(user.getFd(), reply);

			return;
		}

		std::istringstream iss(getParameters()[paramsIndex]);
		long long num;

		if (!(iss >> num))
		{
			if (std::atoll(getParameters()[paramsIndex].c_str()) == 0)
				num = 0;
			else
			{
				std::string reply = ":" + serverName + " 696 " + user.getNickname() + " " + channel->getName() + " l " + getParameters()[paramsIndex] + " :Invalid limit mode parameter. Syntax: <limit>.";

				ft_send(user.getFd(), reply);
				paramsIndex++;

				return;
			}
		}

		if (num == channel->getLimit())
		{
			paramsIndex++;

			return;
		}

		channel->setLimit(num);
		channel->setLimitMode(true);
		changed.push_back(mode);
		changedParams.push_back(getParameters()[paramsIndex]);

		paramsIndex++;
	}
}

void Mode::executeOperatorMode(std::string mode) {}
void Mode::executeTopicMode(std::string mode) {}

void Mode::changeInviteMode()
{
	if (channel->getInviteMode())
		channel->setInviteMode(false);
	else
		channel->setInviteMode(true);
}