#ifndef MODE_HPP
#define MODE_HPP

#include <vector>
#include <sstream>
#include "Command.hpp"
#include "../Channel.hpp"
#include "../UserInfo.hpp"

class Mode : public Command
{
private:
	UserInfo &user;
	std::map<std::string, Channel> &channelList;
	Channel *channel;
	std::string serverName;

	bool flag;
	std::vector<std::string> input;
	std::vector<std::string> removeDup;
	std::vector<std::string> changes;

	bool isValidChannelName();
	std::string getModestring();
	bool isOperator();

public:
	Mode(Message *, UserInfo &, std::map<std::string, Channel> &, std::string);
	~Mode();

	void execute();
};

#endif