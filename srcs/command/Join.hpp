#ifndef JOIN_HPP
#define JOIN_HPP

#include "Command.hpp"
#include "../UserInfo.hpp"
#include "../Message.hpp"
#include "../Channel.hpp"

class Channel;

class Join : public Command {
	private:
		UserInfo &user;
		std::string channelName;
	
	public:
		std::map<std::string, Channel> *channels;
		Channel *channel;
		Join(Message *msg, UserInfo &user, std::map<std::string, Channel> *channels);
		void createChannel();
		void joinChannel();
		void execute();

};

#endif 