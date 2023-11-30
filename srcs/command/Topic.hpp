#ifndef TOPIC_HPP
#define TOPIC_HPP

#include "Command.hpp"
#include "../UserInfo.hpp"
#include "../utils.hpp"
#include "../Channel.hpp"

class Topic : public Command
{
private:
	UserInfo &user;
	std::map<std::string, Channel> channelList;

	bool isError();
	void checkTopic();

public:
	Topic(Message *msg, UserInfo &user, std::map<std::string, Channel> channelList);
	~Topic();
	void execute();
};

#endif