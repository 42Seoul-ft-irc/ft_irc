#ifndef COMMAND_HPP
#define COMMAND_HPP

#include "Server.hpp"

class Command {
	private:
		int fd;
		std::string command;
	public:
		Command(int fd, std::string command);
		int getFd() const;
		int getCommand() const;
		
		// 여기서부터 커맨드 추가

};

#endif