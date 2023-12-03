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

	for (iter = user.channels.begin(); iter != user.channels.end(); iter++)
	{
		if ((*iter).first == partChannelName)
		{
			user.channels.erase(iter);
			return 0;
		}
	}
    return 1;
}

void Part::eraseUserInChannel(Channel *channel, std::string partChannelName)
{
	std::map<std::string, UserInfo>::iterator iterUsers;

	for (iterUsers = channel->users.begin(); iterUsers != channel->users.end(); iterUsers++)
	{
		if ((*iterUsers).first == partChannelName)
			channel->users.erase(iterUsers);
	}
}

void Part::eraseUser(std::string partChannelName)
{
	std::map<std::string, Channel>::iterator iterChannels;

	for (iterChannels = channels->begin(); iterChannels != channels->end(); iterChannels++)
	{
		if ((*iterChannels).second.getName() == partChannelName)
			eraseUserInChannel(&(*iterChannels).second, partChannelName);
	}
}

void Part::partUsers()
{
	for (size_t i = 0; i < partChannelName.size(); i++)
	{
		if (eraseChannelInUserInfo(partChannelName[i]))
		{
			//ft_send();
			return ;
		}
		eraseUser(partChannelName[i]);
		std::string chanMsg = user.getNickname() + "!" + user.getUsername() + "@" + user.getServername() + " PART " + partChannelName[i] + getTrailing();
		std::cout << chanMsg << std::endl;
		ft_send(user.getFd(), chanMsg);
	}
	//std::cout << "-------" << std::endl;
}

void Part::execute()
{
	if (getParameters().size() < 1)
    {
        //ft_send();
        return ;
    }
    if (checkChannel(getParameters().at(0)))
    {
        //ft_send(ERR_NOSUCHCHANNEL);
        return ;
    }
    partUsers();
}