#include "Command.hpp"

Command::Command() {}

Command::Command(Message *message)
{
	fd = message->getFd();
	originalMessage = message->getOriginalMessage();
	command = message->getCommand();
	parameters = message->getParameters();
	trailing = message->getTrailing();
}

// Command::Command(int fd, std::string cmd) : fd(fd), originalMessage(cmd) {}

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

std::vector<std::string> Command::getParameters()
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

// /* originalMessage 파싱하여 command-parameters-trailing 으로 저장 */
// void Command::splitCommand()
// {
// 	std::istringstream iss(originalMessage);
// 	std::string token;

// 	iss >> command;
// 	std::streampos left_position;

// 	while (iss >> token && token[0] != ':' && token.find('\r') == std::string::npos && token.find('\n') == std::string::npos)
// 	{
// 		setParameters(token);
// 		std::cout << token << std::endl;

// 		left_position = iss.tellg();
// 	}

// 	std::string left;
// 	if (left_position != -1)
// 	{
// 		iss.seekg(left_position);
// 		std::getline(iss, left);

// 		if (left[1] == ':')
// 			setTrailing(left.substr(2));
// 	}
// }
/*
 * 여기서부터 커맨드 작성
 * 여기서부터 커맨드 작성
 * 여기서부터 커맨드 작성
 * 여기서부터 커맨드 작성
 */

// void Command::commandPass(Server &server, UserInfo &user)
// {
// 	if (parameters.size() < 2)
// 	{
// 		// send(ERR_NEEDMOREPARAMS)
// 		return;
// 	}
// 	else if (parameters.size() != 2)
// 	{
// 		// send(PASS uses 'PASS passparameter')
// 		return;
// 	}
// 	if (user.getPass())
// 	{
// 		// send(ERR_ALREADYREGISTRED)
// 		return;
// 	}
// 	if (*getParameters()++ == server.getPassword())
// 	{
// 		user.checkPass();
// 		std::cout << "password completed\n";
// 	}
// 	else
// 	{
// 		// send(ERR_PASSWDMISMATCH)
// 	}
// }

// int Command::checkDuplicateNickname(Server &server)
// {
// 	std::map<int, UserInfo>::iterator iter;

// 	for (iter = server.users.begin(); iter != server.users.end(); iter++)
// 	{
// 		if ((*iter).second.getNickname() == parameters[1])
// 			return 1;
// 	}
// 	return 0;
// }

// int Command::checkNicknameForm(Server &server)
// {
// 	if (parameters[1].size() >= 10)
// 	{
// 		// send(ERR_ERRONEUSNICKNAME)
// 		return 1;
// 	}
// 	if (checkDuplicateNickname(server))
// 	{
// 		// send(ERR_NICKNAMEINUSE)
// 		return 1;
// 	}
// 	return 0;
// }

// void Command::commandNick(Server &server, UserInfo &user)
// {
// 	if (parameters.size() < 2)
// 	{
// 		// send(ERR_NEEDMOREPARAMS)
// 	}
// 	else if (parameters.size() != 2)
// 	{
// 		// send(NICK uses 'NICK passparameter')
// 	}
// 	if (user.getNick()) // 원래 유저 닉네임 변경
// 	{
// 		if (!checkNicknameForm(server))
// 			std::cout << "nickname update completed\n";
// 	}
// 	else // 새 유저 닉네임 생성
// 	{
// 		if (!checkNicknameForm(server))
// 		{
// 			user.checkNick();
// 			std::cout << "nickname completed\n";
// 		}
// 	}
// }

std::ostream &operator<<(std::ostream &os, Command &obj)
{
	os << "fd : " << obj.getFd() << std::endl;
	os << "originalMessage : " << obj.getOriginalMessage() << std::endl;
	os << "parameters : { ";

	for (size_t i = 0; i < obj.getParameters().size(); i++)
		os << obj.getParameters()[i] << " / ";

	os << "trailing : " << obj.getTrailing() << std::endl;
	return os;
}
