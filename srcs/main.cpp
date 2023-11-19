#include "Server.hpp"

/*
port: The listening port
password: The connection password
*/
int main(int argc, char **argv)
{
	// todo 인자 예외처리
	Server server;
	// \r\n 나올때까지 입력받기 위해서 클라이언트 수에 맞게 buffer 생성
	char clientBuffer[SOMAXCONN][BUFSIZ];

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
					newone.events = POLLIN;
					pollfds.push_back(newone);
					std::cout << "fd: " << client_fd << std::endl;
					// todo 최대 크기 예외처리
					// todo 서버가 서버에 접근할 때 처리(테스트 해보기)
				}
				// 클라이언트가 메세지 보냈을 때

				for (size_t i = 1; i <= pollfds.size(); i++)
				{
					std::cout << "for문 들어옴\n";

					// 클라이언트가 메시지를 보냄
					if (pollfds[i].revents & POLLIN)
					{
						std::cout << "클라이언트가 메세지 보냄\n";
						
						char buffer[1024];
						int fd = pollfds[i].fd;
						memset(buffer, 0, sizeof(buffer));
						ssize_t recv_byte = recv(fd, buffer, sizeof(buffer), 0);
						if (recv_byte < 0) {
							throw std::runtime_error("Error: Fail read");
						}
						else if (buffer[recv_byte - 2] == '\r' && buffer[recv_byte - 1] == '\n') {
							std::strcat(clientBuffer[fd], buffer);
							std::string recv_str(clientBuffer[fd]);
							std::memset(clientBuffer[fd], 0, BUFSIZ);
							server.checkCommand(recv_str, fd);
							std::cout << fd <<"가 [" << clientBuffer[fd] << "] 라고 보냄";
						}
						else {
							std::strcat(clientBuffer[fd], buffer);
						}
					} //클라이언트가 연결을 끊음
					else if (pollfds[i].revents & POLLHUP)
					{
						std::cout<< "클라이언트가 연결을 끊음\n";
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
