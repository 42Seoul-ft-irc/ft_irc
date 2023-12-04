#include "Kick.hpp"

Kick::Kick(Message *msg, UserInfo &user, std::map<int, UserInfo> *users, std::map<std::string, Channel> *channels) : Command(msg), user(user), users(users), channels(channels){}

Kick::~Kick() {}

int Kick::checkChannel(std::string parameter)
{
	std::map<std::string, Channel>::iterator iter;

	for (iter = channels->begin(); iter != channels->end(); iter++)
	{
		if ((*iter).second.getName() == parameter)
		{
			kickChannel = &(*iter).second;
			return 0;
		}
	}
    return 1;
}

int Kick::checkUser(std::string parameter)
{
	std::map<std::string, bool>::iterator iter;
	for (iter = user.channels.begin(); iter != user.channels.end(); iter++)
	{
		if (iter->first == parameter)
			return 0;
	}
    return 1;
}

int Kick::checkOperator(std::string channel)
{
	std::map<std::string, bool>::iterator iter;

	for (iter = user.channels.begin(); iter != user.channels.end(); iter++)
	{
		if ((*iter).first == channel && (*iter).second == true)
			return 0;
	}
    return 1;
}

int Kick::checkUsers(std::string userName)
{ 
    std::map<std::string, UserInfo>::iterator iter;

	for (iter = kickChannel->users.begin(); iter != kickChannel->users.end(); iter++)
	{
		if ((*iter).first == userName)
		{
			kickUser = &(*iter).second;
			return 0;
		}
	}
    return 1;
}

void Kick::splitParameter(std::string parameter)
{
	size_t commaPos;

	commaPos = parameter.find(',');
	if (commaPos == std::string::npos)
	{
		kickUsersName.push_back(parameter);
		return ;
	}
	while (commaPos != std::string::npos)
	{
		kickUsersName.push_back(parameter.substr(0, commaPos - 1));
		if (!parameter[commaPos + 1] || parameter[commaPos + 1] == ',')
			return ;
		parameter = parameter.substr(commaPos + 1);
		commaPos = parameter.find(',');
	}
	kickUsersName.push_back(parameter);
}

void Kick::eraseChannelInUserInfo(UserInfo *userInfo)
{
	std::map<std::string, bool>::iterator iterChannels;

	for (iterChannels = userInfo->channels.begin(); iterChannels != userInfo->channels.end(); iterChannels++)
	{
		if ((*iterChannels).first == kickChannel->getName())
		{
			userInfo->channels.erase(iterChannels);
			return ;
		}
	}
}

void Kick::eraseUserInChannel(Channel *channel)
{
	std::map<std::string, UserInfo>::iterator iterUsers;

	for (iterUsers = channel->users.begin(); iterUsers != channel->users.end(); iterUsers++)
	{
		if ((*iterUsers).first == kickUser->getNickname())
		{
			channel->users.erase(iterUsers);
			return ;
		}
	}
}

void Kick::eraseUser()
{
	std::map<int, UserInfo>::iterator iterUsers;
	std::map<std::string, Channel>::iterator iterChannels;

	for (iterUsers = users->begin(); iterUsers != users->end(); iterUsers++)
	{
		if ((*iterUsers).second.getNickname() == kickUser->getNickname())
		{
			eraseChannelInUserInfo(&(*iterUsers).second);
			break ;
		}
	}
	for (iterChannels = channels->begin(); iterChannels != channels->end(); iterChannels++)
	{
		if ((*iterChannels).second.getName() == kickChannel->getName())
		{
			eraseUserInChannel(&(*iterChannels).second);
			return ;
		}
	}
}

void Kick::kickUsers(std::string parameter)
{
	splitParameter(parameter);
	for (size_t i = 0; i < kickUsersName.size(); i++)
	{
		if (checkUsers(kickUsersName[i]))
		{
			std::string msg = ":"+user.getHostname()+" 441 " + user.getNickname() + " " + kickUsersName[i] + " " + kickChannel->getName() + " :They are not on that channel";
			ft_send(user.getFd(), msg);
			std::cout << msg << std::endl;
			return ;
		}
		else
		{
			eraseUser();
			std::string msg = ":" + user.getNickname() + "!" + user.getUsername() + "@" + user.getServername() + " KICK " + kickChannel->getName() + " " + kickUser->getNickname() + " :";
			if (!getTrailing().empty())
				msg += getTrailing();
			std::cout << msg << std::endl;
			ft_send(kickUser->getFd(), msg);
		}
	}
	std::string msg = ":" + user.getNickname() + "!" + user.getUsername() + "@" + user.getServername() + " KICK " + kickChannel->getName() + " " + kickUser->getNickname() + " :";
	if (!getTrailing().empty())
		msg += getTrailing();
	std::map<std::string, UserInfo>::iterator iterUsers;
	for (iterUsers = kickChannel->users.begin(); iterUsers !=kickChannel->users.end(); iterUsers++)
		ft_send((*iterUsers).second.getFd(), msg);
}

void Kick::execute()
{
    if (getParameters().size() < 2)
    {
		std::string msg = "461 KICK :Not enough parameters";
		ft_send(user.getFd(), msg);
		return;
    }
    if (checkChannel(getParameters().at(0)))
    {
        std::string msg = ":"+user.getHostname()+" 403 " + user.getNickname() + " " + getParameters().at(0) + " :No such channel";
		ft_send(user.getFd(), msg);
        return ;
    }
	if (checkUser(getParameters().at(0)))
	{
		std::string msg = ":"+user.getHostname()+" 442 " + user.getNickname() + " " + getParameters().at(0) + " :You're not on that channel!";
		ft_send(user.getFd(), msg);
        return ;
	}
    if (checkOperator(kickChannel->getName()))
    {
        std::string msg = ":"+user.getHostname()+" 482 " + user.getNickname() + " " + kickChannel->getName() + " :You must be a channel operator";
		ft_send(user.getFd(), msg);
        return ;
    }
    kickUsers(getParameters().at(1));
}