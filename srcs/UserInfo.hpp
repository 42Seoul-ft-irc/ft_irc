#ifndef USERINFO_HPP
#define USERINFO_HPP

#include <iostream>
#include <string>
#include <map>

class UserInfo {
	private:
		int fd;
		std::string nickname;
		std::string username;
		std::string realname;
		bool pass;
		bool nick;
		bool user;
		bool active;
		
	public:
		UserInfo();

		void setFd(int fd);
		void setNickname(std::string nickname);
		void setUsername(std::string username);
		void setMode(std::string mode);
		void setUnused(std::string unused);
		void setRealname(std::string realname);

		int getFd() const;
		std::string getNickname() const;
		std::string getUsername() const;
		std::string getMode() const;
		std::string getUnused() const;
		std::string getRealname() const;
		bool getPass() const;
		bool getNick() const;
		bool getUser() const;
		bool getActive() const; 

		void checkPass();
		void checkNick();
		void checkuser();
		void checkActive();
		std::map<std::string, bool> channels;
};

std::ostream &operator<<(std::ostream &os, const UserInfo &obj);

#endif