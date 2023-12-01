#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "Server.hpp"

class Channel
{
private:
	std::string name;
	std::string pass;
	std::string topic;
	size_t limit;
	size_t userCount;
	bool isInvite;
	bool isLimit;
	bool isKey;
	bool topicMode;
	bool inviteMode;

public:
	std::map<std::string, UserInfo> operators;
	std::map<std::string, UserInfo> invite;
	std::map<std::string, UserInfo> users;

	Channel(UserInfo &user, std::string name);

	std::string getName() const;
	std::string getPass() const;
	std::string getTopic() const;
	size_t getLimit() const;
	size_t getUserCount() const;
	bool getIsInvite() const;
	bool getIsLimit() const;
	bool getIsKey() const;
	bool getTopicMode() const;
	bool getInviteMode() const;

	void setUserCount(int count);
	void setTopic(std::string);
	void setTopicMode(bool);
	void setInviteMode(bool);
};

std::ostream &operator<<(std::ostream &os, const Channel &obj);

#endif