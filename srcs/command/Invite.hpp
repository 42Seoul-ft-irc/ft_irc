#ifndef INVITE_HPP
#define INVITE_HPP
#include "Command.hpp"

class Invite : public Command {
	private:
		UserInfo &user;
	public:
		std::map<std::string, Channel> *channels;
		Channel *channel;
		
		Invite(Message *msg, UserInfo &user, std::map<std::string, Channel> *channels);
};

#endif