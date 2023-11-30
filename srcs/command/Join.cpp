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
	std::cout << "JOIN success! New channel created.\n";
}

void Join::joinExistingChannel(const std::string &channelName, const std::vector<std::string> &passwordList)
{
	std::map<std::string, Channel>::iterator it2 = this->channels->find(channelName);
	this->channel = &it2->second;

	std::map<std::string, bool>::iterator it_user = this->user.channels.find(channelName);
	if (it_user == this->user.channels.end()) {
		// 사용자가 채널에 없는 경우, 무시하고 계속 진행
		return;
	}
	if (checkJoinConditions(passwordList))
	{
		channel->users.insert(std::make_pair(user.getNickname(), this->user));
		channel->setUserCount(1);

		if (channel->getIsInvite()) {
			channel->invite.erase(user.getNickname());
		}
	}
}

bool Join::checkJoinConditions(const std::vector<std::string> &passwordList)
{
	if (channel->getIsLimit() && channel->getLimit() <= this->channel->users.size())
	{
		std::string msg = "471 " + channel->getName() + " :Cannot join channel (+l)";
		ft_send(this->user.getFd(), msg);
		return false;
	}

	if (channel->getIsKey() && passwordList.empty())
	{
		std::string msg = "461 JOIN :Not enough parameters";
		ft_send(this->user.getFd(), msg);
		return false;
	}
	else if (channel->getIsKey() && passwordList.front() != channel->getPass())
	{
		std::string msg = "475 " + channel->getName() + " :Cannot join channel (+k)";
		ft_send(this->user.getFd(), msg);
		return false;
	}

	if (channel->getIsInvite() && channel->invite.find(user.getNickname()) == channel->invite.end())
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
		ft_send(this->user.getFd(), "461 JOIN :Not enough parameters");
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
