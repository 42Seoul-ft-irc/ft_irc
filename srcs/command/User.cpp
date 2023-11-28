#include "User.hpp"

User::User(Message *msg, UserInfo &user) : Command(msg), user(user) {}

User::~User() {}

void User::execute() {
}
