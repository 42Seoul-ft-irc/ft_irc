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
		std::string hostname;
		std::string servername;
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
		void setHostname(std::string hostname);
		void setServername(std::string servername);
		void setRealname(std::string realname);
		void setMode(std::string mode);
		void setUnused(std::string unused);

		int getFd() const;
		std::string getNickname() const;
		std::string getUsername() const;
		std::string getHostname() const;
		std::string getServername() const;
		std::string getRealname() const;
		std::string getMode() const;
		std::string getUnused() const;
		bool getPass() const;
		bool getNick() const;
		bool getUser() const;
		bool getActive() const; 

		void checkPass();
		void checkNick();
		void checkUser();
		void checkActive();
		std::map<std::string, bool> channels;
};

std::ostream &operator<<(std::ostream &os, const UserInfo &obj);

#endif