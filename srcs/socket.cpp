
#include "Server.hpp"

void create_socket(Server &server)
{
	int socket_fd = socket(AF_INET, SOCK_STREAM, 0);

	if (socket_fd == -1)
		throw std::runtime_error("socket error");

	server.setSocketFd(socket_fd);
}

void open_server(Server &server)
{
	create_socket(server);

	try
	{
		// 소켓 포트 연결
		struct sockaddr_in server_addr;

		std::memset(&server_addr, 0, sizeof(server_addr));
		server_addr.sin_family = AF_INET;
		server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
		server_addr.sin_port = htons(server.getPortNum());

		if (bind(server.getSocketFd(), reinterpret_cast<const struct sockaddr *>(&server_addr), sizeof(server_addr)) == -1)
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
