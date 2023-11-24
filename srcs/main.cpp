#include "Server.hpp"

int main(int argc, char **argv)
{
	try
	{
		Server server(argc, argv);

		//std::cout << "서버 열음\n";
		//std::cout << server.pollfds[0].fd << std::endl;
		while (1)
		{
			int result_fd = poll(server.pollfds.data(), server.pollfds.size(), -1);

			if (result_fd == -1)
				throw std::runtime_error("Error: poll error");

			if (result_fd > 0)
			{
				std::cout << "result_fd: " << result_fd << std::endl;
				// 서버
				if (server.pollfds[0].revents & POLLIN)
				{
					std::cout << "클라이언트가 서버에 접근\n";
					// todo 서버 암호 확인
					server.acceptClient();
				}
				for (size_t i = 1; i <= server.pollfds.size(); i++)
				{
					std::cout << "for문 들어옴\n";
					if (server.pollfds[i].revents & POLLIN)
					{
						std::cout << "클라이언트가 메세지 보냄\n";
						
						char buffer[512];
						int fd = server.pollfds[i].fd;
						memset(buffer, 0, sizeof(buffer));
						ssize_t recv_byte = recv(fd, buffer, sizeof(buffer), 0);
						if (recv_byte < 0) {
							throw std::runtime_error("Error: Fail read");
						}
						else if (buffer[recv_byte - 2] == '\r' && buffer[recv_byte - 1] == '\n') {
							std::strcat(server.clientBuffer[fd], buffer);
							std::cout<<"버퍼에 문자가 추가됨\n";
							std::string recv_str(server.clientBuffer[fd]);
							std::cout << fd <<"가 [" << server.clientBuffer[fd] << "] 라고 보냄\n";
							std::memset(server.clientBuffer[fd], 0, BUFSIZ);
							Command command = server.createCommand(recv_str, fd);
							std::cout << command.getFd() << "'command is created.\n";
							server.executeCommand(command);
						}
						else {
							std::strcat(server.clientBuffer[fd], buffer);
							std::cout<<"버퍼에 문자가 추가됨\n";
						}
					} //클라이언트가 연결을 끊음
					else if (server.pollfds[i].revents & POLLHUP)
					{
						std::cout<< "클라이언트가 연결을 끊음\n";
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
