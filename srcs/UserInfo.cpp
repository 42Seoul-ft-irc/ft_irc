#include "UserInfo.hpp"

void UserInfo::setNickname(std::string nickname)
{
	this->nickname = nickname;
}

void UserInfo::setUsername(std::string username)
{
	this->username = username;
}

void UserInfo::setRealname(std::string realname)
{
	this->realname = realname;
}

std::string UserInfo::getNickname() const
{
	return this->nickname;
}

std::string UserInfo::getUsername() const
{
	return this->username;
}


std::string UserInfo::getRealname() const
{
	return this->realname;
}

UserInfo::UserInfo()
{
	nickname = "";
	username = "";
	hostname = "";
	servername = "";
	realname = "";
}
