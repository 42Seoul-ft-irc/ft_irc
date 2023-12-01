#ifndef TOPIC_HPP
#define TOPIC_HPP

#include "Command.hpp"
#include "../UserInfo.hpp"
#include "../utils.hpp"
#include "../Channel.hpp"

class Channel;

class Topic : public Command
{
private:
	UserInfo &user;
	std::map<std::string, Channel> &channelList;
	std::string serverName;

	bool isError();
	void checkTopic(std::string);
	void editTopic(std::string);

public:
	Topic(Message *, UserInfo &, std::map<std::string, Channel> &, std::string);
	~Topic();
	void execute();
};

#endif