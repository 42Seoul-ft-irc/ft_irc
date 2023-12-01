#include "Mode.hpp"

Mode::Mode(Message *msg, UserInfo &user, std::map<std::string, Channel> &channelList) : Command(msg), user(user), channelList(channelList) {}

Mode::~Mode() {}

void Mode::execute(){}