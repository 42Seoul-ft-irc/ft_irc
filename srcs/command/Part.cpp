#include "Part.hpp"

Part::Part(Message *msg, UserInfo &user, std::map<int, UserInfo> *users, std::map<std::string, Channel> *channels) : Command(msg), user(user), users(users), channels(channels){}

Part::~Part() {}

void Part::splitParameter(std::string parameter)
{
	size_t commaPos;

	commaPos = parameter.find(',');
	if (commaPos == std::string::npos)
	{
		partChannelName.push_back(parameter);
		return ;
	}
	while (commaPos != std::string::npos)
	{
		partChannelName.push_back(parameter.substr(0, commaPos - 1));
		if (!parameter[commaPos + 1] || parameter[commaPos + 1] == ',')
			return ;
		parameter = parameter.substr(commaPos + 1);
		commaPos = parameter.find(',');
	}
	partChannelName.push_back(parameter);
}

int Part::isChannel(std::string partChannelName)
{
	std::map<std::string, Channel>::iterator iter;

	for (iter = channels->begin(); iter != channels->end(); iter++)
	{
		if ((*iter).second.getName() == partChannelName)
			return 0;
	}
    return 1;
}

int Part::checkChannel(std::string parameter)
{
	splitParameter(parameter);
	for (size_t i = 0; i < partChannelName.size(); i++)
	{
		if (isChannel(partChannelName[i]))
			return 1;
	}
	return 0;
}

int Part::eraseChannelInUserInfo(std::string partChannelName)
{
	std::map<std::string, bool>::iterator iter = user.channels.begin();

	for (iter = user.channels.begin(); iter != user.channels.end(); ++iter)
	{
		//std::cout << iter->first << std::endl;
		//std::cout << partChannelName << std::endl;

		if (iter->first == partChannelName)
		{
			user.channels.erase(iter);
			return 0;
		}
	}
    return 1;
}

void Part::eraseUserInChannel(Channel *channel)
{
	std::map<std::string, UserInfo>::iterator iterUsers;

	for (iterUsers = channel->users.begin(); iterUsers != channel->users.end(); ++iterUsers)
	{
		if (iterUsers->first == user.getNickname())
		{
			channel->users.erase(iterUsers);
			channel->operators.erase(iterUsers->first);
			return ;
		}
	}
}

void Part::eraseUser(std::string partChannelName)
{
	std::map<std::string, Channel>::iterator iterChannels;

	for (iterChannels = channels->begin(); iterChannels != channels->end(); iterChannels++)
	{
		if (iterChannels->second.getName() == partChannelName)
		{
			eraseUserInChannel(&(iterChannels->second));
			return ;
		}
	}
}

void Part::partUsers()
{
	for (size_t i = 0; i < partChannelName.size(); i++)
	{
		if (eraseChannelInUserInfo(partChannelName[i]))
		{
			std::string msg = ":"+user.getHostname()+" 442 " + user.getNickname() + " " + partChannelName[i] + " :You're not on that channel";
			ft_send(user.getFd(), msg);
			return ;
		}
		std::cout << partChannelName[i] << std::endl;
		eraseUser(partChannelName[i]);
		std::string chanMsg;
		if (getTrailing().empty())
		{
			std::string lastParameter = getParameters().back();
			chanMsg = ":" + user.getNickname() + "!" + user.getUsername() + "@" + user.getServername() + " PART :" + lastParameter;
		}
		else
			chanMsg = ":" + user.getNickname() + "!" + user.getUsername() + "@" + user.getServername() + " PART " + partChannelName[i] + " :" + getTrailing();
		ft_send(user.getFd(), chanMsg);
		std::map<std::string, UserInfo>::iterator iterUsers;
		partChannel = &(channels->find(partChannelName[i])->second);

		for (iterUsers = partChannel->users.begin(); iterUsers != partChannel->users.end(); iterUsers++)
			ft_send((*iterUsers).second.getFd(), chanMsg);
	}
}

void Part::execute()
{
	if (getParameters().size() < 1)
    {
        std::string msg = "461 " + user.getNickname() + " PART :Not enough parameters";
		ft_send(user.getFd(), msg);
		return;
    }
    if (checkChannel(getParameters().at(0)))
    {
        std::string msg = ":"+user.getHostname()+" 403 " + user.getNickname() + " " + getParameters().at(0) + " :No such channel";
		ft_send(user.getFd(), msg);
        return ;
    }
    partUsers();

}