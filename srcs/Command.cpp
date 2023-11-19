#include "Command.hpp"

Command::Command(int fd, std::string cmd) :fd(fd), command(cmd) { }

int Command::getFd() const {
	return this->fd;
}

std::string Command::getCommand() const {
	return this->command;
}

std::string Command::getOriginalMessage() const {
	return this->original_message;
}

std::string Command::getCommand() const {
	return this->command;
}

/* parameters의 시작 이터레이터 반환 */
std::vector<std::string>::iterator* Command::getParameters() {
	return &this->parameters.begin();
}

std::string Command::getTrailing() const {
	return this->trailing;
}
void Command::setCommand(std::string str) {
	this->command = str;
}
void Command::setParameters(std::string str) {
	this->parameters.push_back(str);
}
void Command::setTrailing(std::string str) {
	this->trailing = str;
}

/* original_message 파싱하여 command-parameters-trailing 으로 저장 */
void Command::splitCommand() {
	std::istringstream iss(this->original_message);
	std::string token;

	iss >> this->command;

	while (iss >> token && token[0] != ':' && token.find('\r') == std::string::npos && token.find('\n') == std::string::npos) {
		this->setParameters(token);
	}

	if (iss >> std::ws && std::getline(iss, this->trailing, '\0')) {
		if (!this->trailing.empty() && this->trailing[0] == ' ') {
			this->trailing = this->trailing.substr(1);
		}
	}
	std::cout<< this->command << "\n" << getTrailing() << "\n" << this->trailing <<"\n";
}

void Command::command_pass() {

}

