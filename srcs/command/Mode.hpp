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

	std::string sign;
	std::vector<std::string> inputModes;
	std::vector<std::string> modes;
	std::vector<std::string> changed;
	std::vector<std::string> changedParams;
	int paramsIndex;

	bool isValidChannelName();
	std::string getModestring();
	bool isOperator();

	void run();
	void saveInputModes(std::string);
	void removeDuplicates();
	void executeModes();
	void executeInviteMode(std::string);
	void executeKeyMode(std::string);
	void executeLimitMode(std::string);
	void executeOperatorMode(std::string);
	void executeTopicMode(std::string);

	void changeInviteMode();

public:
	Mode(Message *, UserInfo &, std::map<std::string, Channel> &, std::string);
	~Mode();

	void execute();
};

#endif