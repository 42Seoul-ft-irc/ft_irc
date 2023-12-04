#ifndef UTILS_HPP
#define UTILS_HPP

#include <vector>
#include <string>
#include "Server.hpp"

class Server;

std::vector<std::string> splitByCRLF(std::string &);
void ft_send(int, std::string);
void ft_quit(Server &, size_t);

#endif