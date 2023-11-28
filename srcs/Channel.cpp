#include "Channel.hpp"

Channel::Channel(UserInfo &user, std::string name) : topic(""), pass(""), limit(0), isInvite(false), isLimit(false), isKey(false) {
	if (name.length() > 200 && name[0] != '#') {
		this->name = name.substr(0, 50);
	}
	operators[user.getNickname()] = &user;
	users[user.getNickname()] = &user;
}