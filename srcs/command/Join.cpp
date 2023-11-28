#include "Join.hpp"

Join::Join(Message *msg, UserInfo &user): Command(*msg), user(user) {

}

