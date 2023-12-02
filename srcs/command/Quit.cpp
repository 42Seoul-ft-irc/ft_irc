#include "Quit.hpp"

Quit::Quit(Message *msg, UserInfo &user, std::map<std::string, Channel> *channels, std::map<int, UserInfo> *users) : Command(msg), user(user) {
	this->channels = channels;
	this->users = users;
}