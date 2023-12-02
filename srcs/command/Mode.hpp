#ifndef MODE_HPP
#define MODE_HPP

#include <vector>
#include <sstream>
#include <algorithm>
#include "Command.hpp"
#include "../Channel.hpp"
#include "../UserInfo.hpp"

class Mode : public Command
{
private:
	UserInfo &user;
	std::map<std::string, Channel> &channelList;
	std::map<int, UserInfo> &users;
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

	void run();
	void saveInputModes(std::string);
	void removeDuplicates();
	void executeModes();
	void executeInviteMode(std::string);
	void executeKeyMode(std::string);
	void executeLimitMode(std::string);
	void executeOperatorMode(std::string);
	void executeTopicMode(std::string);

	bool isNicknameExist(std::string);
	UserInfo *findUserByNickname(std::string);

public:
	Mode(Message *, UserInfo &, std::map<std::string, Channel> &, std::map<int, UserInfo> &, std::string);
	~Mode();

	void execute();
};

#endif