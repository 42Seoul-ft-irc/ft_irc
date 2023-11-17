#include "Server.hpp"

/*
port: The listening port
password: The connection password
*/
int main(int argc, char **argv)
{
	// todo 인자 예외처리
	Server server;

	try
	{
		argv_parsing(argc, argv, server);
		open_server(server);

		std::cout << "서버 열음\n";
		std::vector<pollfd> pollfds(1);
		pollfds[0].fd = server.getSocketFd();
		pollfds[0].events = POLLIN;

		std::cout << pollfds[0].fd << std::endl;

		// kq epoll
		while (1)
		{
			int result_fd = poll(pollfds.data(), pollfds.size(), -1);

			if (result_fd == -1)
				throw std::runtime_error("Error: poll error");

			if (result_fd > 0)
			{
				std::cout << "result_fd: " << result_fd << std::endl;
				// 서버
				if (pollfds[0].revents & POLLIN)
				{
					std::cout << "클라이언트가 서버에 접근\n";
					// todo 서버 암호 확인
					sockaddr_in client;
					socklen_t client_len = sizeof(client);

					int client_fd = accept(server.getSocketFd(), reinterpret_cast<sockaddr *>(&client), &client_len);

					server.users.insert(std::make_pair(client_fd, UserInfo()));
					pollfd newone;
					newone.fd = client_fd;
					pollfds.push_back(newone);
					std::cout << "fd: " << client_fd << std::endl;
					// todo 최대 크기 예외처리
					// todo 서버가 서버에 접근할 때 처리(테스트 해보기)
				}
				// 클라이언트가 메세지 보냈을 때

				for (size_t i = 1; i <= pollfds.size(); i++)
				{
					std::cout << "for문 들어옴\n";

					if (pollfds[i].revents & POLLIN)
					{
						std::cout << "클라이언트가 메세지 보냄\n";
						while (1)
						{
							char buffer[1024];
							memset(buffer, 0, sizeof(buffer));
							ssize_t recv_byte = recv(pollfds[i].fd, buffer, sizeof(buffer), 0);

							std::string recv_str(buffer);
							std::cout << pollfds[i].fd <<"가 [" << buffer << "] 라고 보냄";

							if (recv_str.find("\r\n") != std::string::npos || recv_byte <= 0) // todo \r\n이 맞는가..
								break;
						}
					}
				}

				// 클라이언트
				// user 정보 담는 건 map
				// 닉네임 검사용은 set
				// todo 메세지가 들어왔을 때
				// todo 사용자 나갈 때 POLLHUP
			}
		}
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
}
