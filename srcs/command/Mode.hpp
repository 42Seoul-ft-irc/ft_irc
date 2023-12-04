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

	std::string sign;
	std::vector<std::string> inputModes;
	std::vector<std::string> modes;
	std::vector<std::string> changed;
	std::vector<std::string> changedParams;
	size_t paramsIndex;

	bool isValidChannelName();
	std::string getModestring();

	void run();
	void saveInputModes(std::string);
	void removeDuplicates();
	void executeModes();
	void sendReply();

	void executeInviteMode(std::string);
	void executeKeyMode(std::string);
	void executeLimitMode(std::string);
	void executeOperatorMode(std::string);
	void executeTopicMode(std::string);
	void doesntExistMode(std::string);

	bool isNicknameExist(std::string);
	UserInfo *findUserByNickname(std::string);
	std::string changedModes();

public:
	Mode(Message *, UserInfo &, std::map<std::string, Channel> &, std::map<int, UserInfo> &);
	~Mode();

	void execute();
};

#endif