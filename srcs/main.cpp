#include "Server.hpp"

int main(int argc, char **argv)
{
	try
	{
		Server server(argc, argv);

		std::cout << server.getPortNum() << ", " << server.getSocketFd() << ", " << server.getPassword() << std::endl;

		while (1)
		{
			int resultFd = poll(server.pollfds.data(), server.pollfds.size(), -1);

			if (resultFd == -1)
				throw std::runtime_error("Error: poll error");

			if (resultFd > 0)
			{
				// 서버
				if (server.pollfds[0].revents & POLLIN)
				{
					std::cout << "클라이언트가 서버에 접근\n";
					// todo 서버 암호 확인
					server.acceptClient();
				}
				for (size_t i = 1; i <= server.pollfds.size(); i++)
				{
					if (server.pollfds[i].revents & POLLIN)
					{
						std::cout << "클라이언트가 메세지 보냄\n";

						int fd = server.pollfds[i].fd;

						char buffer[512];
						memset(buffer, 0, sizeof(buffer));

						ssize_t recvByte = recv(fd, buffer, sizeof(buffer), 0);

						if (recvByte < 0)
						{
							throw std::runtime_error("Error: Fail read");
						}
						else
						{
							std::strcat(server.clientBuffer[fd], buffer);
							std::string recvStr(server.clientBuffer[fd]);
							if (recvStr.find("\r\n") == std::string::npos) {
								continue ;
							}
							std::vector<std::string> commands = splitByCRLF(recvStr);

							// std::string으로 복사하여 사용
							std::string strBuffer(server.clientBuffer[fd]);
							std::size_t lastCRLFPos = strBuffer.rfind("\r\n");
							if (lastCRLFPos != std::string::npos) {
								strBuffer.erase(0, lastCRLFPos + 2);
							}

							for (size_t i = 0; i < commands.size(); i++)
							{
								UserInfo &user = server.getUserInfoByFd(fd);
								Command *cmd = server.createCommand(user, commands[i]);
								server.executeCommand(cmd, user);

								std::cout << user << std::endl;
							}
							std::strcpy(server.clientBuffer[fd], strBuffer.c_str());
							//std::cout <<"남은 버퍼: " << strBuffer << std::endl;
						}
					} // 클라이언트가 연결을 끊음
					else if (server.pollfds[i].revents & POLLHUP)
					{
						std::cout << "클라이언트가 연결을 끊음\n";
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

	int result = send(fd, const_cast<char *>(reply), strlen(reply), 0);

	if (result == -1)
		throw std::runtime_error("Error: send error");
}
