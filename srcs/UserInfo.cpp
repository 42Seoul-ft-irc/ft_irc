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

void UserInfo::setHostname(std::string hostname)
{
	this->hostname = hostname;
}

void UserInfo::setServername(std::string servername)
{
	this->servername = servername;
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

std::string UserInfo::getHostname() const
{
	return hostname;
}

std::string UserInfo::getServername() const
{
	return servername;
}

std::string UserInfo::getRealname() const
{
	return realname;
}

bool UserInfo::getPass() const
{
	return pass;
}

bool UserInfo::getNick() const
{
	return nick;
}

bool UserInfo::getUser() const
{
	return user;
}

bool UserInfo::getActive() const
{
	return active;
}

void UserInfo::checkPass()
{
	pass = true;
};

void UserInfo::checkNick()
{
	nick = true;
};

void UserInfo::checkUser()
{
	user = true;
};

void UserInfo::checkActive()
{
	active = true;
}

UserInfo::UserInfo() : nickname(""), username(""), hostname(""), servername(""), realname(""), pass(false), nick(false), user(false), active(false) {}

std::ostream &operator<<(std::ostream &os, const UserInfo &obj)
{
	os << "~~ USERINFO ~~" << std::endl;

	os << "fd : " << obj.getFd() << std::endl;
	os << "nickname : " << obj.getNickname() << std::endl;
	os << "username : " << obj.getUsername() << std::endl;
	os << "hostname : " << obj.getHostname() << std::endl;
	os << "servername : " << obj.getServername() << std::endl;
	os << "realname : " << obj.getRealname() << std::endl
	   << std::endl;

	os << "PASS" << (obj.getPass() ? "✅" : "❌")
	   << " NICK" << (obj.getNick() ? "✅" : "❌")
	   << " USER" << (obj.getUser() ? "✅" : "❌") << " ACTIVE" << (obj.getActive() ? "✅" : "❌") << std::endl;
	os << "~~~~~~~~~~~~~~~~~" << std::endl;

	return os;
}
