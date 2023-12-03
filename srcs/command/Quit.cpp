#include "Quit.hpp"

Quit::Quit(Message *msg, UserInfo &user, std::map<std::string, Channel> *channels, std::map<int, UserInfo> *users, std::vector<pollfd> *pollfds) : Command(msg), user(user)  {
	this->channels = channels;
	this->users = users;
	this->pollfds = pollfds;
}

void Quit::execute() {
	std::string cause = "";

	std::istringstream iss(this->getOriginalMessage());
	std::string command, rest;
	std::getline(iss, command, ':');
	std::getline(iss, rest);
	std::cout << rest << std::endl;
	
	if (rest != "")
		cause = rest;
	else 
		 cause = "leaving";
	
	// response message
	std::string msg = "Error :Closing link: (" + user.getUsername() + "@" + user.getServername() + ") [Quit:" + cause + "]";
	ft_send(user.getFd(), msg);

	// 유저가 join한 채널 확인 후 채널 순회하면서 해당 채널의 users, operator, invite 목록 삭제
	for (std::map<std::string, bool>::iterator chan = user.channels.begin(); chan != user.channels.end(); chan++) {
		std::string chanName = chan->first;
		std::map<std::string, Channel>::iterator chanIt = channels->find(chanName);

		Channel &channel = chanIt->second;
		channel.users.erase(user.getNickname());
		channel.operators.erase(user.getNickname());
		channel.invite.erase(user.getNickname());
		for(std::map<std::string, UserInfo>::iterator userIt = channel.users.begin(); userIt != channel.users.end(); userIt++){
			UserInfo &thisUser = userIt->second;
			if (thisUser.getFd() == user.getFd())
				continue;
			std::cout<<"send user: " << thisUser.getFd() <<std::endl;
			// sooyang!root@127.0.0.1 QUIT :Quit: leaving
			std::string chanMsg = ":" + user.getNickname() + "!" + user.getUsername() + "@" + user.getServername() + " QUIT :Quit: " + cause;
			ft_send(thisUser.getFd(), chanMsg);
		}
	}

	user.checkActive();
}