#include "Server.hpp"

/*
port: The listening port
password: The connection passworda
*/
int main(int argc, char **argv)
{
	// todo 인자 예외처리
	Server server;

	try
	{
		parsing(argc, argv, server);
		open_server(server);

		std::vector<pollfd> pollfds(1);
		pollfds[0].fd = server.getSocketFd();
		pollfds[0].events = POLLIN;

		std::map<int, userInfo> users; // todo 클래스에 넣을지 

		while (1)
		{
			int result = poll(pollfds.data(), pollfds.size(), -1); // Wait indefinitely

			if (result == -1)
				throw std::runtime_error("Error: poll error");

			if (result > 0)
			{
				// 서버
				if (pollfds[0].revents & POLLIN)
				{
					// todo 유저 만들고
					// user 정보 담는 건 map
					// 닉네임 검사용은 set
					int clientSocket = accept()
					// todo 최대 크기 예외처리 
				}
				// 클라이언트
			}
		}
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
}
