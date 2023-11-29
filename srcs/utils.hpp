#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>

std::vector<std::string> splitByCRLF(std::string& input);
void ft_send(int fd, char *msg);

#endif