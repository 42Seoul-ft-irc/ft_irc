#include "Server.hpp"

int convert_port(char *portStr)
{
	for (size_t i = 0; i < strlen(portStr); i++)
		if (!isdigit(portStr[i]))
			throw std::invalid_argument("Error: invalid argument");

	int port = atoi(portStr);

	if (port < 0 || 65535 < port)
		throw std::invalid_argument("Error: invalid argument");

	return port;
}

void argv_parsing(int argc, char **argv, Server &server)
{
	if (argc != 3)
		throw std::invalid_argument("Error: invalid argument");

	server.setPortNum(convert_port(argv[1]));

	std::string password(argv[2]);
	server.setPassword(password);
}
