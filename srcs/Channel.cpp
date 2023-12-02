#include "Channel.hpp"

Channel::Channel(UserInfo &user, std::string name) : pass(""), topic(""), limit(0), userCount(1), inviteMode(false), keyMode(false), limitMode(false), topicMode(true)
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
std::string Channel::getPass() const{
	return pass;
}
std::string Channel::getTopic() const{
	return topic;
}
size_t Channel::getLimit() const{
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

/* 채팅방 인원 추가하고 싶으면 매개변수에 1, 퇴장시키고 싶으면 매개변수에 2 넣어주세요 */
void Channel::setUserCount(int count){
	this->userCount = static_cast<size_t>(static_cast<int>(this->userCount) + count);
}

void Channel::setTopic(std::string topic)
{
	this->topic = topic;
}

void Channel::setTopicMode(bool mode)
{
	topicMode = mode;
}
void Channel::setInviteMode(bool mode)
{
	inviteMode = mode;
}

std::ostream &operator<<(std::ostream &os, const Channel &obj) {
	os << "~~ CHANNEL ~~" << std::endl;
	os << "name: " << obj.getName() << std::endl;
	os << "password: " << obj.getPass() << " (" << obj.getKeyMode() << ")"<< std::endl;
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