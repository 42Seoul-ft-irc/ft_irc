#include JOIN_HPP
#define JOIN_HPP

#include "Command.hpp"
#include "UserInfo.hpp"
#include "Message.hpp"
#include "Channel.hpp"

class Join : public Command {
	private:
		UserInfo &user;
		Channel &channel;
		std::string channelName;
	
	public:
		Join(Message *msg, UserInfo &user);
		void execute();

};

#endif 