#include "Command.hpp"

Command::Command(int fd, std::string cmd) :fd(fd), command(cmd) { }

int Command::getFd() const {
	return this->fd;
}

std::string Command::getCommand() const {
	return this->command;
}

