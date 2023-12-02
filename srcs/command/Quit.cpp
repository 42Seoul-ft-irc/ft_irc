#include "Quit.hpp"

Quit::Quit(Message *msg, UserInfo &user, std::map<std::string, Channel> *channels, std::map<int, UserInfo> *users) : Command(msg), user(user) {
	this->channels = channels;
	this->users = users;
}

void Quit::execute() {
	// 유저가 join한 채널 확인 후 채널 순회하면서 해당 채널의 users, operator, invite 목록 삭제
	
	// 서버 내 users에서 해당 유저 삭제 

	// response message
}