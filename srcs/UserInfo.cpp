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
	return fd;
}

std::string UserInfo::getNickname() const
{
	return nickname;
}

std::string UserInfo::getUsername() const
{
	return username;
}


std::string UserInfo::getRealname() const
{
	return realname;
}

bool UserInfo::getPass() const {
	return pass;
}

bool UserInfo::getNick() const {
	return nick;
}

bool UserInfo::getUser() const {
	return user;
}

bool UserInfo::getActive() const {
	return active;
}

void UserInfo::checkPass(){
	pass = true;
};
void UserInfo::checkNick(){
	nick = true;
};
void UserInfo::checkuser(){
	user = true;
};
void UserInfo::checkActive(){
	active = true;
}

UserInfo::UserInfo(): nickname(""), username(""), realname(""), pass(false), nick(false), user(false), active(false) { }

std::ostream &operator<<(std::ostream &os, const UserInfo &obj)
{
	os << "~~ USERINFO ~~" << std::endl;

	os << "fd : " << obj.getFd() << std::endl;
	os << "nickname : " << obj.getNickname() << std::endl;
	os << "username : " << obj.getUsername() << std::endl;
	os << "realname : " << obj.getRealname() << std::endl << std::endl;

	os << "PASS : " << (obj.getPass() ? "✅" : "❌") << std::endl;
	os << "NICK : " << (obj.getNick() ? "✅" : "❌") << std::endl;
	os << "USER : " << (obj.getUser() ? "✅" : "❌") << std::endl;
	os << "ACTIVE : " << (obj.getActive() ? "✅" : "❌") << std::endl << std::endl;

	return os;
}
