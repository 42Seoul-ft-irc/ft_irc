#include "Server.hpp"
int main(int argc, char **argv)
{
	try
	{
		Server server(argc, argv);
		std::cout << server.getPortNum() << ", " << server.getSocketFd() << ", " << server.getPassword() << std::endl;
		while (1)
		{
			int resultFd = poll(server.pollfds.data(), server.pollfds.size(), 3600);
			if (resultFd == -1)
				throw std::runtime_error("Error: poll error");
			if (resultFd > 0)
			{
				if (server.pollfds[0].revents & POLLIN)
				{
					std::cout << "클라이언트가 서버에 접근\n";
					server.acceptClient();
					continue;
				}
				for (size_t i = 1; i < server.pollfds.size(); i++)
				{
					if (i != 0 && server.pollfds[i].revents == 0)
						continue;
					if (server.pollfds[i].revents & POLLHUP || server.pollfds[i].revents & POLLERR)
					{
						ft_quit(server, i);
						std::cout << "클라이언트가 연결을 끊음\n";
					}
					else if (server.pollfds[i].revents & POLLIN)
					{
						std::cout << "클라이언트가 메세지 보냄: "<< i << "\n";
						int fd = server.pollfds[i].fd;
						char buffer[512];
						memset(buffer, 0, sizeof(buffer));
						ssize_t recvByte = recv(fd, buffer, sizeof(buffer), 0);
						if (recvByte < 0)
							throw std::runtime_error("Error: Fail read");
						else
						{
							std::strcat(server.clientBuffer[fd], buffer);
							std::string recvStr(server.clientBuffer[fd]);
							if (recvStr.find("\r\n") == std::string::npos)
								continue ;

							std::vector<std::string> commands = splitByCRLF(recvStr);
							std::string strBuffer(server.clientBuffer[fd]);
							std::size_t lastCRLFPos = strBuffer.rfind("\r\n");
							if (lastCRLFPos != std::string::npos)
								strBuffer.erase(0, lastCRLFPos + 2);

							for (size_t i = 0; i < commands.size(); i++)
							{
								std::cout << "들어온 메세지 : " << commands[i] << std::endl;
								try {
									UserInfo &user = server.getUserInfoByFd(fd);
									Command *cmd = server.createCommand(user, commands[i]);
									server.executeCommand(cmd, user);
								} catch (const std::exception &e){
									std::cerr << e.what() << std::endl;
									continue;
								}
							}
							std::strcpy(server.clientBuffer[fd], strBuffer.c_str());
							//std::cout <<"남은 버퍼: " << strBuffer << std::endl;
						}
					}
				}
			}
		}
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
}
std::vector<std::string> splitByCRLF(std::string& input) {
	std::vector<std::string> result;
	size_t start = 0;
	size_t found = input.find("\r\n");
	while (found != std::string::npos)
	{
		result.push_back(input.substr(start, found - start));
		start = found + 2; 
		found = input.find("\r\n", start);
	}
	return result;
}

void ft_send(int fd, std::string str)
{
    str += "\r\n";
	const char *reply = str.c_str();

	std::cout << str;

	int result = send(fd, const_cast<char *>(reply), strlen(reply), 0);

	if (result == -1)
		throw std::runtime_error("Error: send error");
}

void ft_quit(Server &server, size_t i)
{
	UserInfo &user = server.getUserInfoByFd(server.pollfds[i].fd);

	for (std::map<std::string, bool>::iterator chan = user.channels.begin(); chan != user.channels.end(); chan++)
	{
		std::string chanName = chan->first;
		std::map<std::string, Channel>::iterator chanIt = server.channels.find(chanName);

		Channel &channel = chanIt->second;
		channel.users.erase(user.getNickname());
		channel.operators.erase(user.getNickname());
		channel.invite.erase(user.getNickname());

		for (std::map<std::string, UserInfo>::iterator userIt = channel.users.begin(); userIt != channel.users.end(); userIt++)
		{
			UserInfo &thisUser = userIt->second;
			if (thisUser.getFd() == user.getFd())
				continue;
			std::cout << "send user: " << thisUser.getFd() << std::endl;
			std::string chanMsg = ":" + user.getNickname() + "!" + user.getUsername() + "@" + user.getServername() + " QUIT :Quit: leaving";
			ft_send(thisUser.getFd(), chanMsg);
		}
	}
	server.users.erase(user.getFd());
	close(user.getFd());
	server.pollfds.erase(server.pollfds.begin() + i);
}