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
	bool isInvite;
	bool isLimit;
	bool isKey;

public:
	std::map<std::string, UserInfo> operators;
	std::map<std::string, UserInfo> invite;
	std::map<std::string, UserInfo> users;

	Channel(UserInfo &user, std::string name);
	std::string getName() const;
	std::string getPass() const;
	std::string getTopic() const;
	size_t getLimit() const;
	bool getIsInvite() const;
	bool getIsLimit() const;
	bool getIsKey() const;
};


#endif