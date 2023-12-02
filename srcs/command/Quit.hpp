#pragma once
#include "../Server.hpp"

class Message;
class UserInfo;
class Channel;

class Quit : public Command {
	private:
		UserInfo &user;

	public:
		std::map<std::string, Channel> *channels;
		std::map<int, UserInfo> *users;
		Quit(Message *msg, UserInfo &user, std::map<std::string, Channel> *channels, std::map<int, UserInfo> *users);
		void execute();
};