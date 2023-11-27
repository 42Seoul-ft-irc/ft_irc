#include "Message.hpp"

Message::Message(int fd, std::string cmd) : fd(fd), originalMessage(cmd)
{
	splitMsg();
}

int Message::getFd() const
{
	return fd;
}

std::string Message::getCommand() const
{
	return command;
}

std::string Message::getOriginalMessage() const
{
	return originalMessage;
}

/* parameters의 시작 이터레이터 반환 */
std::vector<std::string>::iterator Message::getParametersBegin()
{
	return parameters.begin();
}

std::vector<std::string> Message::getParameters() const
{
	return parameters;
}

std::string Message::getTrailing() const
{
	return trailing;
}

void Message::setCommand(std::string str)
{
	this->command = str;
}

void Message::setParameters(std::string str)
{
	this->parameters.push_back(str);
}
void Message::setTrailing(std::string str)
{
	this->trailing = str;
}

/* originalMessage 파싱하여 Message-parameters-trailing 으로 저장 */
void Message::splitMsg()
{
	std::istringstream iss(originalMessage);
	std::string token;

	iss >> command;
	std::streampos left_position;

	while (iss >> token && token[0] != ':' && token.find('\r') == std::string::npos && token.find('\n') == std::string::npos)
	{
		setParameters(token);
		std::cout << token << std::endl;

		left_position = iss.tellg();
	}

	std::string left;
	if (left_position != -1)
	{
		iss.seekg(left_position);
		std::getline(iss, left);

		if (left[1] == ':')
			setTrailing(left.substr(2));
	}
}

std::ostream &operator<<(std::ostream &os, const Message &obj)
{
	os << "~~ MESSAGE ~~" << std::endl;

	os << "fd : " << obj.getFd() << std::endl;
	os << "originalMessage : " << obj.getOriginalMessage() << std::endl;
	os << "parameters : { ";

	for (size_t i = 0; i < obj.getParameters().size(); i++)
		os << obj.getParameters()[i] << "  ";
	os << "}\ntrailing : " << obj.getTrailing() << std::endl;
	os << "~~~~~~~~~~~~~~~~" << std::endl;

	return os;
}
