
#include "Server.hpp"

void create_socket(Server &server)
{
	int socketFd = socket(AF_INET, SOCK_STREAM, 0);

	if (socketFd == -1)
		throw std::runtime_error("socket error");

	server.setSocketFd(socketFd);
}

void open_server(Server &server)
{
	create_socket(server);

	try
	{
		// 소켓 포트 연결
		struct sockaddr_in serverAddr;

		std::memset(&serverAddr, 0, sizeof(serverAddr));
		serverAddr.sin_family = AF_INET;
		serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
		serverAddr.sin_port = htons(server.getPortNum());

		if (bind(server.getSocketFd(), reinterpret_cast<const struct sockaddr *>(&serverAddr), sizeof(serverAddr)) == -1)
			throw std::runtime_error("Error: bind error");

		if (listen(server.getSocketFd(), SOMAXCONN) == -1)
			throw std::runtime_error("Error: listen error");
	}
	catch (const std::exception &e)
	{
		close(server.getSocketFd());
		throw std::runtime_error(e.what());
	}
}
