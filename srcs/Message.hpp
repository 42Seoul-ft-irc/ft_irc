#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <string>
#include <vector>
#include <sstream>
#include <iostream>

class Message
{
private:
	int fd;
	std::string originalMessage;
	std::string command;
	std::vector<std::string> parameters;
	std::string trailing;

public:
	Message(int, std::string);
	void splitMsg();

	// getter
	int getFd() const;
	std::string getOriginalMessage() const;
	std::string getCommand() const;
	std::vector<std::string> getParameters() const;
	std::vector<std::string>::iterator getParametersBegin();
	std::string getTrailing() const;

	// setter
	void setCommand(std::string);
	void setParameters(std::string);
	void setTrailing(std::string);
	void setParentValue(std::string, std::vector<std::string>, std::string);
};

std::ostream &operator<<(std::ostream &os, const Message &obj);

#endif