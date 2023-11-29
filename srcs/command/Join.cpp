#include "Join.hpp"

Join::Join(Message *msg, UserInfo &user, std::map<std::string, Channel> *channels) : Command(msg), user(user)
{
	this->channels = channels;
}

void Join::createChannel() {
	std::cout<< this->getParameters().at(0) << std::endl;
	Channel channel(this->user, this->getParameters().at(0));
	this->channels->insert(std::make_pair(this->getParameters().at(0), channel));
	channel.operators.insert(std::make_pair(user.getNickname(), this->user));
	channel.users.insert(std::make_pair(user.getNickname(), this->user));

	std::map<std::string, Channel>::iterator it2 = this->channels->find(this->getParameters().at(0));
	this->channel = &it2->second;

	std::cout << "JOIN 성공! 새로운 채널이 생성됨. channel name: " << this->channel->getName() <<"\n";
}

void Join::joinChannel() {
	
}

void Join::execute()
{
	std::cout<< "join line 10\n";
	// 매개변수 없을 때
	if (this->getParameters().size() < 1)
	{
			std::cout<< "join line 10\n";
		// ERR_NEEDMOREPARAMS
		return;
	}
	std::cout<< "join line 18\n";
	// 사용자가 가입한 채널이 10개인지 확인
	if (this->user.channels.size() >= 10)
	{
		std::cout<< "join line 22\n";
		// ERR_TOOMANYCHANNELS
		return;
	}
	std::cout<< "join line 26\n";
	// 존재하는 채널인지 확인 => 채널 생성 및 운영자 설정
	std::map<std::string, Channel>::iterator it1 = this->channels->find(this->getParameters().at(0));
	if (it1 == channels->end()) {
		createChannel();
		return ;
	}
	// 조인의 대상 채널 지정
	std::map<std::string, Channel>::iterator it2 = this->channels->find(this->getParameters().at(0));
	this->channel = &it2->second;
	// 사용자가 채널에 없는지 확인
	std::map<std::string, bool>::iterator it_user = this->user.channels.find(this->getParameters().at(0));
	if (it_user == this->user.channels.end()) {
		// command 무시하고 넘어가기
		return ;
	}
	// 인원수 제한 확인
	else if (channel->getIsLimit() && channel->getLimit() <= this->channel->users.size()) {
		//ERR_CHANNELISFULL
		return ;
	} 
	// 채널 비밀번호 확인
	else if (channel->getIsKey() && (this->getParameters().size() < 2 || this->getParameters().at(1) != channel->getPass())) {
		//ERR_NEEDMOREPARAMS
		return ;
	}
	else {
		joinChannel();
		return ;
	}
}
