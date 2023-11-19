#ifndef COMMAND_HPP
#define COMMAND_HPP

#include "Server.hpp"

class Command {
	private:
		int fd;
		std::string original_message;
		std::string command;
		std::vector<std::string> parameters;
		std::string trailing;
	public:
		Server &server;

		Command(int fd, std::string command);
		int getFd() const;
		std::string getOriginalMessage() const;
		std::string getCommand() const;
		std::vector<std::string>::iterator *getParameters();
		std::string getTrailing() const;
		void setCommand(std::string);
		void setParameters(std::string);
		void setTrailing(std::string);

		void splitCommand();

		// 여기서부터 커맨드 추가
		void command_pass();
};

#endif