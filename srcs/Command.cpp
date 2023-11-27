#include "Command.hpp"

Command::Command(Message *message)
{
	fd = message->getFd();
	originalMessage = message->getOriginalMessage();
	command = message->getCommand();
	parameters = message->getParameters();
	trailing = message->getTrailing();
}

Command::~Command()
{
}

int Command::getFd() const
{
	return fd;
}

std::string Command::getCommand() const
{
	return command;
}

std::string Command::getOriginalMessage() const
{
	return originalMessage;
}

/* parameters의 시작 이터레이터 반환 */
std::vector<std::string>::iterator Command::getParametersBegin()
{
	return parameters.begin();
}

std::vector<std::string> Command::getParameters() const
{
	return parameters;
}

std::string Command::getTrailing() const
{
	return trailing;
}
void Command::setCommand(std::string str)
{
	this->command = str;
}
void Command::setParameters(std::string str)
{
	this->parameters.push_back(str);
}
void Command::setTrailing(std::string str)
{
	this->trailing = str;
}

std::ostream &operator<<(std::ostream &os, const Command &obj)
{
	os << "fd : " << obj.getFd() << std::endl;
	os << "originalMessage : " << obj.getOriginalMessage() << std::endl;
	os << "parameters : { ";

	for (size_t i = 0; i < obj.getParameters().size(); i++)
		os << obj.getParameters()[i] << " / ";

	os << "trailing : " << obj.getTrailing() << std::endl;
	return os;
}
