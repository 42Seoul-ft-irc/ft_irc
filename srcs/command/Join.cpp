#include "Join.hpp"

Join::Join(Message *msg, UserInfo &user, std::map<std::string, Channel> *channels) : Command(msg), user(user)
{
	this->channels = channels;
}

static std::vector<std::string> splitByComma(std::string &input)
{
	std::vector<std::string> result;
	size_t start = 0;
	size_t found = input.find(',');

	while (found != std::string::npos)
	{
		result.push_back(input.substr(start, found - start));
		start = found + 1;
		found = input.find(',', start);
	}
	result.push_back(input.substr(start));
	return result;
}

void Join::handleChannelJoin(const std::string &channelName, const std::vector<std::string> &passwordList)
{
	if (this->user.channels.size() >= 10)
	{
		std::string msg = "405 " + channelName + " :You have joined too many channels";
		ft_send(this->user.getFd(), msg);
		return;
	}
	std::map<std::string, Channel>::iterator it1 = this->channels->find(channelName);
	if (it1 == this->channels->end()) {
		if (channelName[0] != '#')
			return ;
		createAndJoinNewChannel(channelName);
	}
	else {
		joinExistingChannel(channelName, passwordList);
	}
}

void Join::createAndJoinNewChannel(const std::string &channelName)
{
	Channel channel(this->user, channelName);
	this->channels->insert(std::make_pair(channelName, channel));
	channel.operators.insert(std::make_pair(user.getNickname(), this->user));
	channel.users.insert(std::make_pair(user.getNickname(), this->user));
	user.channels.insert(std::make_pair(channel.getName(), true));
	std::string msg = ":" + this->user.getNickname() + "!" + this->user.getUsername() + "@" + this->user.getServername() + " " + "JOIN :" + this->getParameters().at(0) + "\n";
	msg += "353 " + this->user.getNickname() + " = " + this->getParameters().at(0) + " : @" + this->user.getNickname() + "\n";
	msg += "366 " + this->user.getNickname() + " " + this->getParameters().at(0) + " :End of /NAMES list.";
	ft_send(this->user.getFd(), msg);
}

void Join::joinExistingChannel(const std::string &channelName, const std::vector<std::string> &passwordList)
{
	std::map<std::string, Channel>::iterator it2 = this->channels->find(channelName);
	this->channel = &it2->second;

	std::map<std::string, bool>::iterator it_user = this->user.channels.find(channelName);
	if (it_user != this->user.channels.end())
		return;
	if (checkJoinConditions(passwordList))
	{
		channel->users.insert(std::make_pair(user.getNickname(), this->user));
		user.channels.insert(std::make_pair(channel->getName(), false));
		channel->setUserCount(1);

		if (channel->getInviteMode()) {
			channel->invite.erase(user.getNickname());
		}

		std::string msg = ":" + this->user.getNickname() + "!" + this->user.getUsername() + "@" + this->user.getServername() + " " + "JOIN :" + this->getParameters().at(0) + "\n";
		msg += "353 " + this->user.getNickname() + " = " + this->getParameters().at(0) + " :";
		for (std::map<std::string, UserInfo>::iterator i = channel->users.begin(); i != channel->users.end(); i++) {
			UserInfo user_info = i->second;
			std::map<std::string, UserInfo>::iterator it = channel->operators.find(user_info.getNickname());
			if (it == channel->operators.end())
				msg += " " + user_info.getNickname();
			else
				msg += " @" + user_info.getNickname();
		}
		msg += "\n";
		msg += "366 " + this->user.getNickname() + " " + this->getParameters().at(0) + " :End of /NAMES list.";
		ft_send(this->user.getFd(), msg);
		std::cout << msg;
	}
}

bool Join::checkJoinConditions(const std::vector<std::string> &passwordList)
{
	if (channel->getLimitMode() && channel->getLimit() <= this->channel->users.size())
	{
		std::string msg = "471 " + channel->getName() + " :Cannot join channel (+l)";
		ft_send(this->user.getFd(), msg);
		return false;
	}

	if (channel->getKeyMode() && passwordList.empty())
	{
		std::string msg = "461 JOIN :Not enough parameters";
		ft_send(this->user.getFd(), msg);
		return false;
	}
	else if (channel->getKeyMode() && passwordList.front() != channel->getKey())
	{
		std::string msg = "475 " + channel->getName() + " :Cannot join channel (+k)";
		ft_send(this->user.getFd(), msg);
		return false;
	}

	if (channel->getInviteMode() && channel->invite.find(user.getNickname()) == channel->invite.end())
	{
		std::string msg = "473 " + channel->getName() + " :Cannot join channel (+i)";
		ft_send(this->user.getFd(), msg);
		return false;
	}

	return true;
}

void Join::execute()
{
	std::vector<std::string> channelList;
	std::vector<std::string> passwordList;

	if (this->getParameters().size() < 1)
	{
		std::cout << "parameter error \n";
		std::string msg = "461 JOIN :Not enough parameters";
		ft_send(this->user.getFd(), msg);
		return;
	}
	else if (this->getParameters().size() >= 1)
	{
		channelList = splitByComma(this->getParameters().at(0));
		if (this->getParameters().size() >= 2) {
			passwordList = splitByComma(this->getParameters().at(1));
		}
	}

	for (size_t i = 0; i < channelList.size(); ++i)
	{
		const std::string &channelName = channelList[i];
		handleChannelJoin(channelName, passwordList);
	}
}
