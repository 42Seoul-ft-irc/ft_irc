#ifndef INVITE_HPP
#define INVITE_HPP
#include "Command.hpp"
#include "../UserInfo.hpp"
#include "../Channel.hpp"

class UserInfo;
class Channel;

class Invite : public Command {
	private:
		UserInfo &user;
	public:
		Channel *channel;
		std::map<std::string, Channel> *channels;
		std::map<int, UserInfo> *users;
		
		Invite(Message *msg, UserInfo &user, std::map<std::string, Channel> *channels, std::map<int, UserInfo> *users);
		void execute();
};

#endif