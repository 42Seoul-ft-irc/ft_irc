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
					std::cout << "for문 i = " << i << std::endl;

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
						else if (buffer[recvByte - 2] == '\r' && buffer[recvByte - 1] == '\n')
						{
							std::strcat(server.clientBuffer[fd], buffer);
							std::cout << "버퍼에 문자가 추가됨1\n";
							std::string recvStr(server.clientBuffer[fd]);
							std::cout << fd << "가 [" << server.clientBuffer[fd] << "] 라고 보냄\n";
							std::memset(server.clientBuffer[fd], 0, BUFSIZ);

							Command *cmd = server.createCommand(fd, recvStr);
							server.executeCommand(cmd);
						}
						else
						{
							std::strcat(server.clientBuffer[fd], buffer);
							std::cout << "버퍼에 문자가 추가됨2\n"
									  << buffer << std::endl;
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

void ft_send(int fd, char *msg)
{
    int result = send(fd, msg, strlen(msg), 0);

    if (result == -1)
        throw std::runtime_error("Error: send error");
}
