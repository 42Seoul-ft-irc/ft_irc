#include "Invite.hpp"

Invite::Invite(Message *msg, UserInfo &user, std::map<std::string, Channel> *channels, std::map<int, UserInfo> *users) : Command(msg), user(user)
{
	this->channels = channels;
	this->users = users;
}

void Invite::execute() {
	// argument 확인 (2개 이상)
	if (this->getParameters().size() < 2) {
		std::string msg = "461 INVITE :Not enough parameters";
		ft_send(this->user.getFd(), msg);
		return ;
	}
	// 초대받을 유저 존재하는지 확인
	std::map<int, UserInfo>::iterator user_it = this->users->begin();
	for( ; user_it != this->users->end(); ++user_it) {
		if (user_it->second.getNickname() == this->getParameters().at(0)) {
			this->client = &user_it->second;
			break;
		}
	}
	if (user_it == this->users->end()) {
		std::string msg = "401 " + this->getParameters().at(0) +" :No such nick";
		ft_send(this->user.getFd(), msg);
		return ;
	}
	// 채널 존재하는지 확인
	std::map<std::string, Channel>::iterator chan_it = this->channels->find(this->getParameters().at(1));
	if (chan_it == this->channels->end()) {
		std::string msg = "403 " + this->getParameters().at(1) +" :No such channel";
		ft_send(user.getFd(), msg);
		return ;
	}
	this->channel = &chan_it->second;
	// 채널에 초대받을 유저가 있는지 확인
	std::map<std::string, UserInfo>::iterator chan_user_it = this->channel->users.find(this->getParameters().at(0));
	if (chan_user_it != this->channel->users.end()) {
		std::string msg = "443 " + this->getParameters().at(0) + " " + this->getParameters().at(1) +" :is already on channel";
		ft_send(user.getFd(), msg);
		return ;
	}
	// 채널의 operator인지 확인
	std::map<std::string, UserInfo>::iterator operator_it = this->channel->operators.find(this->user.getNickname());
	if (operator_it == this->channel->operators.end()){
		std::string msg = "482 " + this->getParameters().at(1) + " :You're not channel operator";
		ft_send(user.getFd(), msg);
		return ;
	}
	// 채널 invite 목록에 넣고 341 반환, 초대받는 대상에게는 메시지 반환
	this->channel->operators[this->getParameters().at(1)] = *this->client;
	std::string msg = "341 " + this->user.getNickname() + " " + this->getParameters().at(1) + " :" + this->getParameters().at(0);
	ft_send(user.getFd(), msg);
	msg.clear();
	msg = "INVITE " + this->getParameters().at(0) + " :" + this->getParameters().at(1);
	ft_send(this->client->getFd(), msg);
}