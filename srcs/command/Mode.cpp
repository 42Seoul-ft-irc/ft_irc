#include "Mode.hpp"

Mode::Mode(Message *msg, UserInfo &user, std::map<std::string, Channel> &channelList, std::map<int, UserInfo> &users) : Command(msg), user(user), channelList(channelList), users(users), paramsIndex(2) {}

Mode::~Mode() {}

void Mode::execute()
{
	if (!user.getActive())
		return;

	if (!getParameters().size())
		return;

	if (!isValidChannelName())
		return;

	if (getParameters().size() == 1) // modestring 없는 경우 324 RPL_CHANNELMODEIS
	{
		std::map<std::string, Channel>::iterator it = channelList.find(getParameters()[0]);

		this->channel = &(it->second);

		std::string modestring = getModestring();
		std::string reply = ":" + user.getHostname() + " 324 " + user.getNickname() + " " + getParameters()[0] + " " + modestring;

		ft_send(user.getFd(), reply);
		return;
	}

	if (getParameters()[1].length() < 2)
		return;

	if (getParameters()[1][0] != '+' && getParameters()[1][0] != '-')
		return;

	if (!channel->isOperator(user.getNickname()))
	{
		std::string reply = ":" + user.getHostname() + " 482 " + user.getNickname() + " " + channel->getName() + " :You're not channel operator";

		ft_send(user.getFd(), reply);
		return;
	}

	run();
}

bool Mode::isValidChannelName()
{
	std::string channelName = getParameters()[0];

	if (channelName[0] != '#') // 401 ERR_NOSUCHNICK
	{
		std::string reply = ":" + user.getHostname() + " 401 " + user.getNickname() + " " + channelName + " :No such nick";
		ft_send(user.getFd(), reply);

		return false;
	}
	else // 403 ERR_NOSUCHCHANNEL
	{
		std::map<std::string, Channel>::iterator it = channelList.find(channelName);

		if (it == channelList.end())
		{
			std::string reply = ":" + user.getHostname() + " 403 " + user.getNickname() + " " + channelName + " :No such channel";
			ft_send(user.getFd(), reply);

			return false;
		}
		else
			channel = &(it->second);
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

void Mode::run()
{
	std::string modestring = getParameters()[1];

	saveInputModes(modestring);
	removeDuplicates();
	executeModes();

	if (changed.size())
		sendReply();
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
			doesntExistMode(mode);
			break;
		}
	}
}

void Mode::sendReply()
{
	std::string str = changedModes();
	int paramSize = changedParams.size();

	if (!paramSize)
		str = " :" + str;
	else
	{
		str = " " + str;
		int i;
		for (i = 0; i < paramSize - 1; i++)
			str = str + " " + changedParams[i];
		str = str + " :" + changedParams[i];
	}
	std::map<std::string, UserInfo>::iterator it = channel->users.begin();

	for (; it != channel->users.end(); ++it)
	{
		UserInfo userInfo = it->second;

		std::string reply = ":" + user.getNickname() + "!" + userInfo.getHostname() + "@" + userInfo.getServername() + " MODE " + channel->getName() + str;

		ft_send(userInfo.getFd(), reply);
	}
}

void Mode::executeInviteMode(std::string mode)
{
	if (mode == "+i" && channel->getInviteMode())
		return;
	else if (mode == "-i" && !channel->getInviteMode())
		return;

	channel->changeInviteMode();
	changed.push_back(mode);
}

void Mode::executeKeyMode(std::string mode)
{
	if (paramsIndex > getParameters().size() - 1)
	{
		std::string reply = ":" + user.getHostname() + " 696 " + user.getNickname() + " " + channel->getName() + " k * :You must specify a parameter for the key mode. Syntax: <key>.";

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
			std::string reply = ":" + user.getHostname() + " 467 " + user.getNickname() + " " + channel->getName() + " :Channel key already set";

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
	else if (mode == "+l")
	{
		if (paramsIndex > getParameters().size() - 1) // 파라미터 없을 때
		{
			std::string reply = ":" + user.getHostname() + " 696 " + user.getNickname() + " " + channel->getName() + " l * :You must specify a parameter for the limit mode. Syntax: <limit>.";

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
				std::string reply = ":" + user.getHostname() + " 696 " + user.getNickname() + " " + channel->getName() + " l " + getParameters()[paramsIndex] + " :Invalid limit mode parameter. Syntax: <limit>.";

				ft_send(user.getFd(), reply);
				paramsIndex++;

				return;
			}
		}

		if (num < 0)
		{
			std::string reply = ":" + user.getHostname() + " 696 " + user.getNickname() + " " + channel->getName() + " l " + getParameters()[paramsIndex] + " :Invalid limit mode parameter. Syntax: <limit>.";

			ft_send(user.getFd(), reply);
			paramsIndex++;

			return;
		}

		if (num == channel->getLimit())
		{
			paramsIndex++;

			return;
		}

		std::stringstream ss;
		ss << num;

		std::string strNumber = ss.str();
		channel->setLimit(num);
		channel->setLimitMode(true);
		changed.push_back(mode);
		changedParams.push_back(strNumber);

		paramsIndex++;
	}
}

void Mode::executeOperatorMode(std::string mode)
{
	if (paramsIndex > getParameters().size() - 1) // 파라미터 없을 때
	{
		std::string reply = ":" + user.getHostname() + " 696 " + user.getNickname() + " " + channel->getName() + " o * :You must specify a parameter for the op mode. Syntax: <nick>.";

		ft_send(user.getFd(), reply);

		return;
	}

	std::string name = getParameters()[paramsIndex];

	if (!isNicknameExist(name))
	{
		std::string reply = ":" + user.getHostname() + " 401 " + user.getNickname() + " " + name + " :No such nick";

		ft_send(user.getFd(), reply);
		paramsIndex++;

		return;
	}

	if (channel->isOperator(name) && mode == "-o")
	{
		std::map<std::string, UserInfo>::iterator it = channel->operators.find(name);

		channel->operators.erase(it);
		changeUserInfo(*findUserByNickname(name), false);
		changed.push_back(mode);
		changedParams.push_back(name);
	}
	else if (!channel->isOperator(name) && mode == "+o")
	{
		channel->operators.insert(std::make_pair(name, *findUserByNickname(name)));
		changeUserInfo(*findUserByNickname(name), true);
		changed.push_back(mode);
		changedParams.push_back(name);
	}

	paramsIndex++;
}

void Mode::executeTopicMode(std::string mode)
{
	if ((mode == "+t" && !channel->getTopicMode()) || (mode == "-t" && channel->getTopicMode()))
	{
		channel->changeTopicMode();
		changed.push_back(mode);
	}
}

void Mode::doesntExistMode(std::string mode)
{
	mode.erase(0, 1);
	std::string reply = ":" + user.getHostname() + " 472 " + user.getNickname() + " " + mode + " :is not a recognised channel mode.";

	ft_send(user.getFd(), reply);
}

bool Mode::isNicknameExist(std::string name)
{
	std::map<int, UserInfo>::iterator it = users.begin();

	for (; it != users.end(); ++it)
		if (it->second.getNickname() == name)
			return true;

	return false;
}

UserInfo *Mode::findUserByNickname(std::string name)
{
	std::map<int, UserInfo>::iterator it = users.begin();

	for (; it != users.end(); ++it)
		if (it->second.getNickname() == name)
			return &(it->second);

	return 0;
}

std::string Mode::changedModes()
{
	std::string str = changed[0];
	char flag;

	if (changed[0][0] == '+')
		flag = '+';
	else
		flag = '-';

	for (size_t i = 1; i < changed.size(); ++i)
	{
		if (changed[i][0] == flag)
			str += changed[i].erase(0, 1);
		else
		{
			str += changed[i];
			flag = changed[i][0];
		}
	}

	return str;
}

void Mode::changeUserInfo(UserInfo &user, bool type)
{
	std::map<std::string, bool>::iterator it = user.channels.begin();

	for (; it != user.channels.end(); ++it)
		if (it->first == channel->getName())
			user.channels[it->first] = type;
}
