#include "Command.hpp"

Command::Command(int fd, std::string cmd) : fd(fd), original_message(cmd) {}

int Command::getFd() const
{
	return this->fd;
}

std::string Command::getCommand() const
{
	return this->command;
}

std::string Command::getOriginalMessage() const
{
	return this->original_message;
}

/* parameters의 시작 이터레이터 반환 */
std::vector<std::string>::iterator Command::getParameters()
{
	return this->parameters.begin();
}

std::string Command::getTrailing() const
{
	return this->trailing;
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

/* original_message 파싱하여 command-parameters-trailing 으로 저장 */
void Command::splitCommand()
{
	std::istringstream iss(this->original_message);
	std::string token;

	iss >> this->command;
	std::streampos left_position;

	while (iss >> token && token[0] != ':' && token.find('\r') == std::string::npos && token.find('\n') == std::string::npos)
	{
		this->setParameters(token);
		std::cout << token << std::endl;

		left_position = iss.tellg();
	}

	std::string left;
	if (left_position != -1)
	{
		iss.seekg(left_position);
		std::getline(iss, left);

		if (left[1] == ':')
			this->setTrailing(left.substr(2));
	}
}
/*
 * 여기서부터 커맨드 작성
 * 여기서부터 커맨드 작성
 * 여기서부터 커맨드 작성
 * 여기서부터 커맨드 작성
 */

void Command::command_pass(Server &server, UserInfo &user)
{
	if (this->parameters.size() < 2)
	{
		// send(ERR_NEEDMOREPARAMS)
	}
	else if (this->parameters.size() != 2)
	{
		// send(PASS uses 'PASS passparameter')
	}
	if (user.getPass())
	{
		// send(ERR_ALREADYREGISTRED)
	}
	if (*this->getParameters()++ == server.getPassword())
	{
		user.checkPass();
		std::cout << "password completed\n";
	}
	else
	{
		// send(ERR_PASSWDMISMATCH)
	}
}

int Command::checkDuplicateNickname(Server &server)
{
	std::map<int, UserInfo>::iterator iter;

	for (iter = server.users.begin(); iter != server.users.end(); iter++)
	{
		if ((*iter).second.getNickname() == parameters[1])
			return 1;
	}
	return 0;
}

int Command::checkNicknameForm(Server &server)
{
	if (this->parameters[1].size() >= 10)
	{
		// send(ERR_ERRONEUSNICKNAME)
		return 1;
	}
	if (checkDuplicateNickname(server))
	{
		// send(ERR_NICKNAMEINUSE)
		return 1;
	}
	return 0;
}

void Command::commandNick(Server &server, UserInfo &user)
{
	if (this->parameters.size() < 2)
	{
		// send(ERR_NEEDMOREPARAMS)
	}
	else if (this->parameters.size() != 2)
	{
		// send(NICK uses 'NICK passparameter')
	}
	if (user.getNick()) //원래 유저 닉네임 변경
	{
		if (!checkNicknameForm(server))
			std::cout << "nickname update completed\n";
	}
	else //새 유저 닉네임 생성
	{
		if (!checkNicknameForm(server))
		{
			user.checkNick();
			std::cout << "nickname completed\n";
		}
	}
}

void Command::commandUser()
{
	
}
