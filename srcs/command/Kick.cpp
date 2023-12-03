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
			userInfo->channels.erase(iterChannels);
	}
}

void Kick::eraseUserInChannel(Channel *channel)
{
	std::map<std::string, UserInfo>::iterator iterUsers;

	for (iterUsers = channel->users.begin(); iterUsers != channel->users.end(); iterUsers++)
	{
		if ((*iterUsers).first == kickChannel->getName())
			channel->users.erase(iterUsers);
	}
}

void Kick::eraseUser()
{
	std::map<int, UserInfo>::iterator iterUsers;
	std::map<std::string, Channel>::iterator iterChannels;

	for (iterUsers = users->begin(); iterUsers != users->end(); iterUsers++)
	{
		if ((*iterUsers).second.getNickname() == kickUser->getNickname())
			eraseChannelInUserInfo(&(*iterUsers).second);
	}
	for (iterChannels = channels->begin(); iterChannels != channels->end(); iterChannels++)
	{
		if ((*iterChannels).second.getName() == kickChannel->getName())
			eraseUserInChannel(&(*iterChannels).second);
	}
}

void Kick::kickUsers(std::string parameter)
{
	splitParameter(parameter);
	for (size_t i = 0; i < kickUsersName.size(); i++)
	{
		if (checkUsers(kickUsersName[i]))
		{
			//ft_send();
		}
		else
		{
			eraseUser();
			std::string chanMsg = user.getNickname() + "!" + user.getUsername() + "@" + user.getServername() + " KICK " + kickChannel->getName() + " " + kickUser->getNickname();
			ft_send(user.getFd(), chanMsg);
		}
	}
}

void Kick::execute()
{
    if (getParameters().size() < 2)
    {
        //ft_send();
        return ;
    }
    if (checkChannel(getParameters().at(0)))
    {
        //ft_send(ERR_NOSUCHCHANNEL);
        return ;
    }
    if (checkOperator(kickChannel->getName()))
    {
        //ft_send(ERR_CHANOPRIVSNEEDED);
        return ;
    }
    kickUsers(getParameters().at(1));
}