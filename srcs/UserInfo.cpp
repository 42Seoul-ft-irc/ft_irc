#include "UserInfo.hpp"

void UserInfo::setFd(int fd)
{
	this->fd = fd;
}

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

int UserInfo::getFd() const
{
	return this->fd;
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

bool UserInfo::getPass() const {
	return this->pass;
}

bool UserInfo::getNick() const {
	return this->nick;
}

bool UserInfo::getUser() const {
	return this->user;
}

void UserInfo::checkPass(){
	this->pass = true;
};
void UserInfo::checkNick(){
	this->nick = true;
};
void UserInfo::checkuser(){
	this->user = true;
};

UserInfo::UserInfo(): nickname(""), username(""), hostname(""), servername(""), realname(""), pass(false), nick(false), user(false) { }
