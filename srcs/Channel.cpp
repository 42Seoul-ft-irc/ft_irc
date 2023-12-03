#include "Channel.hpp"

Channel::Channel(UserInfo &user, std::string name) : key(""), topic(""), limit(0), userCount(1), inviteMode(false), keyMode(false), limitMode(false), topicMode(true)
{

	if (name.length() > 200) {
		this->name = name.substr(0, 200);
	}
	else {
		this->name = name;
	}
	operators[user.getNickname()] = user;
	users[user.getNickname()] = user;
}

std::string Channel::getName() const{
	return name;
}
std::string Channel::getKey() const
{
	return key;
}
std::string Channel::getTopic() const{
	return topic;
}
long long Channel::getLimit() const
{
	return limit;
}
size_t Channel::getUserCount() const{
	return userCount;
}
bool Channel::getInviteMode() const
{
	return inviteMode;
}
bool Channel::getKeyMode() const
{
	return keyMode;
}
bool Channel::getLimitMode() const
{
	return limitMode;
}
bool Channel::getTopicMode() const
{
	return topicMode;
}

void Channel::setKey(std::string key)
{
	this->key = key;
}
void Channel::setTopic(std::string topic)
{
	this->topic = topic;
}

void Channel::setLimit(size_t limit)
{
	this->limit = limit;
}

/* 채팅방 인원 추가하고 싶으면 매개변수에 1, 퇴장시키고 싶으면 매개변수에 -1 넣어주세요 */
void Channel::setUserCount(int count)
{
	this->userCount = static_cast<size_t>(static_cast<int>(this->userCount) + count);
}

void Channel::setInviteMode(bool mode)
{
	inviteMode = mode;
}

void Channel::setKeyMode(bool mode)
{
	keyMode = mode;
}
void  Channel::setLimitMode(bool mode)
{
	limitMode = mode;
}
void Channel::setTopicMode(bool mode)
{
	topicMode = mode;
}

void Channel::changeInviteMode()
{
	if (inviteMode)
		inviteMode = false;
	else
		inviteMode = true;
}

void Channel::changeTopicMode()
{
	if (topicMode)
		topicMode = false;
	else
		topicMode = true;
}

bool Channel::isOperator(std::string nickname)
{
	std::map<std::string, UserInfo>::iterator it = operators.find(nickname);

	if (it == operators.end())
		return false;
	return true;
}

std::ostream &operator<<(std::ostream &os, const Channel &obj) {
	os << "~~ CHANNEL ~~" << std::endl;
	os << "name: " << obj.getName() << std::endl;
	os << "password: " << obj.getKey() << " (" << obj.getKeyMode() << ")" << std::endl;
	os << "topic: " << obj.getTopic() << std::endl;
	os << "limit: " << obj.getLimit() << " (" << obj.getLimitMode() << ")" <<std::endl;
	os << "userCount: " << obj.getUserCount() << std::endl;
	os << "inviteMode: " << obj.getInviteMode() << std::endl;
	os << "keyMode: " << obj.getKeyMode() << std::endl;
	os << "limitMode: " << obj.getLimitMode() << std::endl;
	os << "topicMode: " << obj.getTopicMode() << std::endl;
	os << "~~~~~~~~~~~~~~~~" << std::endl;
	return os;
}