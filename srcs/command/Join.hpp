#ifndef JOIN_HPP
#define JOIN_HPP

#include "Command.hpp"
#include "../utils.hpp"
#include "../UserInfo.hpp"
#include "../Message.hpp"
#include "../Channel.hpp"

class Channel;

class Join : public Command
{
private:
	UserInfo &user;
	std::string channelName;

public:
	std::map<std::string, Channel> *channels;
	Channel *channel;
	Join(Message *msg, UserInfo &user, std::map<std::string, Channel> *channels);
	int handleChannelJoin(const std::string &channelName, const std::vector<std::string> &passwordList);
	void createAndJoinNewChannel(const std::string &channelName);
	void joinExistingChannel(const std::string &channelName, const std::vector<std::string> &passwordList);
	bool checkJoinConditions(const std::vector<std::string> &passwordList);
	void execute();
};

#endif 