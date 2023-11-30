#include "Invite.hpp"

Invite::Invite(Message *msg, UserInfo &user, std::map<std::string, Channel> *channels, std::map<int, UserInfo> *users) : Command(msg), user(user)
{
	this->channels = channels;
	this->users = users;
}

void Invite::execute() {
	// argument 확인 (2개 이상)
	if (this->getParameters().size() < 2) {
		ft_send(user.getFd(), const_cast<char *>("461 INVITE :Not enough parameters\r\n"));
		return ;
	}
	// 초대받을 유저 존재하는지 확인
	std::map<int, UserInfo>::iterator user_it = this->users->begin();
	for( ; user_it != this->users->end(); ++user_it) {
		if (user_it->second.getNickname() == this->getParameters().at(0)) {
			this->user = user_it->second;
			break;
		}
	}


	// 채널 존재하는지 확인
	std::map<std::string, Channel>::iterator chan_it = this->channels->find(this->getParameters().at(1));
	if (chan_it == this->channels->end()) {
		ft_send(user.getFd(), const_cast<char *>("403 INVITE :Not enough parameters\r\n"));
		return ;
	}
	
	// 채널의 operator인지 확인

	

	// 채널에 초대받을 유저가 있는지 확인

	// 채널 invite 목록에 넣고 341 반환

}