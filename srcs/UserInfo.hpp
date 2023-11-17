#ifndef USERINFO_HPP
#define USERINFO_HPP

#include "Server.hpp"

class UserInfo {
	private:
		std::string nickname;
		std::string username;
		std::string mode;
		std::string unused;
		std::string realname;
	public:
		UserInfo();
		~UserInfo();

		void setNickname(std::string nickname);
		void setUsername(std::string username);
		void setMode(std::string mode);
		void setUnused(std::string unused);
		void setRealname(std::string realname);

		std::string getNickname() const;
		std::string getUsername() const;
		std::string getMode() const;
		std::string getUnused() const;
		std::string getRealname() const;
};

#endif;