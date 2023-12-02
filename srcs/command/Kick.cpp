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

void Kick::eraseUser()
{
	std::map<std::string, UserInfo>::iterator iterUsers;
	std::map<std::string, bool>::iterator iterChannels;

	for (iterUsers = kickChannel->users.begin(); iterUsers != kickChannel->users.end(); iterUsers++)
	{
		if ((*iterUsers).first == kickUser->getNickname())
			//kickUser = &(*iterUsers).second;
	}
	for (iterChannels = kickUser->channels.begin(); iterChannels != kickUser->channels.end(); iterChannels++)
	{
		if ((*iterChannels).first == kickChannel->getName())
			//kickUser = &(*iterUsers).second;
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