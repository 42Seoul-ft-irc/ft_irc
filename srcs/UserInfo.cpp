#include "UserInfo.hpp"

void UserInfo::setNickname(std::string nickname){
	this->nickname = nickname;
}

void UserInfo::setUsername(std::string username){
	this->username = username;
}

void UserInfo::setMode(std::string mode){
	this->mode = mode;
}

void UserInfo::setUnused(std::string unused){
	this->unused = unused;
}

void UserInfo::setRealname(std::string realname){
	this->realname = realname;
}

std::string UserInfo::getNickname() const{
	return this->nickname;
}

std::string UserInfo::getUsername() const{
	return this->username;
}

std::string UserInfo::getMode() const{
	return this->mode;
}

std::string UserInfo::getUnused() const{
	return this->unused;
}

std::string UserInfo::getRealname() const{
	return this->realname;
}