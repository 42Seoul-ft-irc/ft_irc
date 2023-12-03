#pragma once
#include "../Server.hpp"

class Message;
class UserInfo;
class Channel;

class Quit : public Command {
	private:
		UserInfo& user;

	public:
		size_t i;
		std::map<std::string, Channel> *channels;
		std::map<int, UserInfo> *users;
		std::vector<pollfd> *pollfds;
		Quit(Message *msg, UserInfo& user, std::map<std::string, Channel> *channels, std::map<int, UserInfo> *users, std::vector<pollfd> *pollfds);
		void execute();
};