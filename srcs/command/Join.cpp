#include "Join.hpp"

Join::Join(Message *msg, UserInfo &user, std::map<std::string, Channel> *channels) : Command(msg), user(user)
{
	this->channels = channels;
}

static std::vector<std::string> splitByComma(std::string &input)
{
	std::vector<std::string> result;

	size_t start = 0;
	size_t found = input.find(',');

	while (found != std::string::npos)
	{
		result.push_back(input.substr(start, found - start));
		start = found + 1;
		found = input.find(',', start);
	}
	result.push_back(input.substr(start));

	return result;
}

void Join::execute()
{
	std::vector<std::string> channelList;
	std::vector<std::string> passwordList;

	if (this->getParameters().size() < 1)
	{
		std::cout << "parameter error \n";
		ft_send(this->user.getFd(), const_cast<char *>("461 JOIN :Not enough parameters\r\n"));
		return;
	}
	else if (this->getParameters().size() >= 1)
	{
		channelList = splitByComma(this->getParameters().at(0));
		if (this->getParameters().size() >= 2)
		{
			passwordList = splitByComma(this->getParameters().at(1));
		}
	}
	for (size_t i = 0; i < channelList.size(); i++)
	{
		// 사용자가 가입한 채널이 10개인지 확인
		if (this->user.channels.size() >= 10)
		{
			std::string msg = "405 " + this->channel->getName() + " :You have joined too many channels\r\n";
			ft_send(this->user.getFd(), const_cast<char *>(msg.c_str()));
			return;
		}
		// 존재하는 채널인지 확인 => 채널 생성 및 운영자 설정
		std::map<std::string, Channel>::iterator it1 = this->channels->find(channelList.at(i));
		if (it1 == channels->end())
		{
			Channel channel(this->user, channelList.at(i));
			this->channels->insert(std::make_pair(channelList.at(i), channel));
			channel.operators.insert(std::make_pair(user.getNickname(), this->user));
			channel.users.insert(std::make_pair(user.getNickname(), this->user));
			// join 성공 후 리턴
			std::cout << "JOIN 성공! 새로운 채널이 생성됨. \n";
			continue;
		}
		// 조인의 대상 채널 지정
		std::map<std::string, Channel>::iterator it2 = this->channels->find(channelList.at(i));
		this->channel = &it2->second;
		// 사용자가 채널에 없는지 확인
		std::map<std::string, bool>::iterator it_user = this->user.channels.find(channelList.at(i));
		if (it_user == this->user.channels.end())
		{
			// command 무시하고 넘어가기
			continue;
		}
		// 인원수 제한 확인
		if (channel->getIsLimit() && channel->getLimit() <= this->channel->users.size())
		{
			std::string msg = "471 " + channel->getName() + " :Cannot join channel (+l)\r\n";
			ft_send(this->user.getFd(), const_cast<char *>(msg.c_str()));
			continue;
		}
		// 채널 비밀번호 확인
		if (channel->getIsKey() && passwordList.at(i).empty())
		{
			std::string msg = "461 JOIN :Not enough parameters\r\n";
			ft_send(this->user.getFd(), const_cast<char *>(msg.c_str()));
			continue;
		}
		else if (channel->getIsKey() && passwordList.at(i) != channel->getPass())
		{
			std::string msg = "475 " + channel->getName() + " :Cannot join channel (+k)\r\n";
			ft_send(this->user.getFd(), const_cast<char *>(msg.c_str()));
			continue;
		}
		// 초대모드인 경우 초대된 사용자 확인
		if (channel->getIsInvite()) {
			std::map<std::string, UserInfo>::iterator invite_it = channel->invite.find(user.getNickname());
			if (invite_it == channel->invite.end()){
				std::string msg = "473 " + channel->getName() + " :Cannot join channel (+i)\r\n";
				ft_send(this->user.getFd(), const_cast<char *>(msg.c_str()));
				continue;
			}
		}
		// 기존 채널에 사용자 추가
		channel->users.insert(std::make_pair(user.getNickname(), this->user));
		channel->setUserCount(1);
		if (channel->getIsInvite()) {
			channel->invite.erase(user.getNickname());
		}
	}
}
