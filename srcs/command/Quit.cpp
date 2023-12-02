#include "Quit.hpp"

Quit::Quit(Message *msg, UserInfo &user, std::map<std::string, Channel> *channels, std::map<int, UserInfo> *users) : Command(msg), user(user) {
	this->channels = channels;
	this->users = users;
}

void Quit::execute() {
	bool channelCheck = false;
	// 유저가 join한 채널 확인 후 채널 순회하면서 해당 채널의 users, operator, invite 목록 삭제
	for (std::map<std::string, bool>::iterator chan = user.channels.begin(); chan != user.channels.end(); chan++) {
		std::string chanName = chan->first;
		std::map<std::string, Channel>::iterator chanIt = channels->find(chanName);

		Channel &channel = chanIt->second;
		channel.users.erase(user.getNickname());
		channel.operators.erase(user.getNickname());
		channel.invite.erase(user.getNickname());
		channelCheck = true;
	}
	// 서버 내 users에서 해당 유저 삭제 
	users->erase(user.getFd());

	// response message
	std::string cause;
	if (this->getParameters().size() >= 1){
		for(size_t i = 0; i < this->getParameters().size(); i++) {
			cause += this->getParameters().at(0);
			if (i != this->getParameters().size() - 1)
				cause += " ";
		}
	}
	else 
		 cause = "leaving";
	std::string msg = "Error :Closing link: (" + user.getUsername() + "@" + user.getServername() + ") [Quit:" + cause + "]";
	ft_send(user.getFd(), msg);

	if (channelCheck) {
		// sooyang!root@127.0.0.1 QUIT :Quit: leaving
		std::string chanMsg = user.getNickname() + "!" + user.getUsername() + "@" + user.getServername() + " QUIT: QUIT: " + cause;
		ft_send(user.getFd(), chanMsg);
	}
}