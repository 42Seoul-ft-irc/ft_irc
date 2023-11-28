#include "Channel.hpp"

Channel::Channel(UserInfo &user, std::string name) : pass(""), topic(""), limit(0), isInvite(false), isLimit(false), isKey(false) {
	if (name.length() > 200 && name[0] != '#') {
		this->name = name.substr(0, 200);
	}
	operators[user.getNickname()] = &user;
	users[user.getNickname()] = &user;
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
bool Channel::getIsInvite() const{
	return this->isInvite;
}
bool Channel::getIsLimit() const{
	return this->isLimit;
}
bool Channel::getIsKey() const{
	return this->isKey;
}