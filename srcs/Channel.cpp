#include "Channel.hpp"

Channel::Channel(UserInfo &user, std::string name) : pass(""), topic(""), limit(0), userCount(1), isInvite(false), isLimit(false), isKey(false) {
	
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
	return this->name;
}
std::string Channel::getPass() const{
	return this->pass;
}
std::string Channel::getTopic() const{
	return this->topic;
}
size_t Channel::getLimit() const{
	return this->limit;
}
size_t Channel::getUserCount() const{
	return this->userCount;
}
bool Channel::getIsInvite() const{
	return this->isInvite;
}
bool Channel::getIsLimit() const{
	return this->isLimit;
}
bool Channel::getIsKey() const{
	return this->isKey;
}
/* 채팅방 인원 추가하고 싶으면 매개변수에 1, 퇴장시키고 싶으면 매개변수에 2 넣어주세요 */
void Channel::setUserCount(int count){
	this->userCount = static_cast<size_t>(static_cast<int>(this->userCount) + count);
}

void Channel::setTopic(std::string topic)
{
	this->topic = topic;
}

std::ostream &operator<<(std::ostream &os, const Channel &obj) {
	os << "~~ CHANNEL ~~" << std::endl;
	os << "name: " << obj.getName() << std::endl;
	os << "password: " << obj.getPass() << " (" << obj.getIsKey() << ")"<< std::endl;
	os << "topic: " << obj.getTopic() << std::endl;
	os << "limit: " << obj.getLimit() << " (" << obj.getIsLimit() << ")" <<std::endl;
	os << "userCount: " << obj.getUserCount() << std::endl;
	os << "isInvite: " << obj.getIsInvite() << std::endl;
	os << "isKey: " << obj.getIsKey() << std::endl;
	os << "~~~~~~~~~~~~~~~~" << std::endl;
	return os;
}