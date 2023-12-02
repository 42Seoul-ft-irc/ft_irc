#include "Kick.hpp"

Kick::Kick(Message *msg, UserInfo &user, std::map<int, UserInfo> users, std::map<std::string, Channel> channels) : Command(msg), user(user), users(users), channels(channels){}

Kick::~Kick() {}

int Kick::isChannel(std::string channel)
{
	std::map<std::string, Channel>::iterator iter;

	for (iter = channels.begin(); iter != channels.end(); iter++)
	{
		if ((*iter).second.getName() == channel)
		{
			kickChannels.push_back((*iter).second);
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
		kickChannelsName.push_back(parameter);
		return ;
	}
	while (commaPos != std::string::npos)
	{
		kickChannelsName.push_back(parameter.substr(0, commaPos - 1));
		if (!parameter[commaPos + 1] || parameter[commaPos + 1] == ',')
			return ;
		parameter = parameter.substr(commaPos + 1);
		commaPos = parameter.find(',');
	}
	kickChannelsName.push_back(parameter);
}

int Kick::checkChannels(std::string parameter)
{
    splitParameter(parameter);
    for (size_t i = 0; kickChannelsName.size(); i++)
	{
		if (isChannel(kickChannelsName[i]))
			return 1;
	}
	return 0;
}

int Kick::isOperator(std::string channel)
{ 
    std::map<std::string, bool>::iterator iter;

	for (iter = user.channels.begin(); iter != user.channels.end(); iter++)
	{
		if ((*iter).first == channel && (*iter).second == true)
			return 0;
	}
    return 1;
}

int Kick::checkOperator()
{
    for (size_t i = 0; kickChannels.size(); i++)
	{
		if (isOperator(kickChannels[i]))
			return 1;
	}
	return 0;
}

void Kick::execute()
{
    if (getParameters().size() < 2)
    {
        //ft_send();
        return ;
    }
    if (checkChannels(getParameters().at(0)))
    {
        //ft_send(ERR_NOSUCHCHANNEL);
        return ;
    } //�޸�����. �ִ� ä������ Ȯ��
    if (checkOperator())
    {
        //ft_send(ERR_CHANOPRIVSNEEDED);
        return ;
    }//���� �� ä�ο� ������� Ȯ��
    if (checkUsers())
    {

    }//�޸�����. �� ä�ο� ����ڰ� �ִ��� Ȯ��
    //Ŀ��Ʈ Ȯ��?
    //ä�μ� ����� ����
}