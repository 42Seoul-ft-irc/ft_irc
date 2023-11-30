#include "Invite.hpp"

Invite::Invite(Message *msg, UserInfo &user, std::map<std::string, Channel> *channels) : Command(msg), user(user)
{
	this->channels = channels;
}

void Invite::execute() {
	// argument 확인 (2개 이상)
	if (this->getParameters().size() < 2) {
		ft_send(user.getFd(), const_cast<char *>("461 INVITE :Not enough parameters\r\n"));
		return ;
	}
	// 채널 존재하는지 확인
	
	// 채널의 operator인지 확인

	// 초대받을 유저 존재하는지 확인

	// 채널에 초대받을 유저가 있는지 확인

	// 채널 invite 목록에 넣고 341 반환

}