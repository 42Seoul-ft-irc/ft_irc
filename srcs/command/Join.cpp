#include "Join.hpp"

Join::Join(Message *msg, UserInfo &user, std::map<std::string, Channel> *channels) : Command(msg), user(user)
{
	this->channels = channels;
}

void Join::execute()
{
	// 매개변수 없을 때
	if (this->getParameters().size() < 2)
	{
		// ERR_NEEDMOREPARAMS
		return;
	}
	// 존재하는 채널인지 확인
	std::map<std::string, Channel>::iterator it1 = this->channels->find(this->getParameters().at(1));
	if (it1 == channels->end()){	
		this->channels->insert(std::make_pair(this->getParameters().at(1), Channel(this->user, this->getParameters().at(1))));
	}
	// 조인의 대상 채널 지정
	std::map<std::string, Channel>::iterator it2 = this->channels->find(this->getParameters().at(1));
	this->channel = &it2->second;

	// 사용자가 채널에 없는지 확인
	

	// 사용자가 가입한 채널이 10개인지 확인
	if (this->user.channels.size() >= 10)
	{
		// ERR_TOOMANYCHANNELS
		return;
	}
	//if ()
	//{
	//}
}
