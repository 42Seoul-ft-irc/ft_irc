#include "Invite.hpp"

Invite::Invite(Message *msg, UserInfo &user, std::map<std::string, Channel> *channels) : Command(msg), user(user)
{
	this->channels = channels;
}

void Invite::execute() {
	
}