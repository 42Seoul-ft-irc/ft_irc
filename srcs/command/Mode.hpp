#ifndef MODE_HPP
#define MODE_HPP

#include <vector>
#include "Command.hpp"
#include "../Channel.hpp"
#include "../UserInfo.hpp"

class Mode : public Command
{
private:
	UserInfo &user;
	std::map<std::string, Channel> &channelList;

	bool flag;
	std::vector<std::string> input;
	std::vector<std::string> removeDup;
	std::vector<std::string> changes;

public:
	Mode(Message *, UserInfo &, std::map<std::string, Channel> &);
	~Mode();

	void execute();
};

#endif