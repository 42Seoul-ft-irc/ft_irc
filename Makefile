.DEFAULT_GOAL=all

CXX = c++
CXXFLAGS =  -Wall -Wextra -Werror -std=c++98 -MMD -MP
RM = rm -rf
NAME = ircserv
SRCS = main.cpp \
		Server.cpp \
		Channel.cpp \
		UserInfo.cpp \
		Message.cpp \
		Auth.cpp \
		command/Command.cpp \
		command/Pass.cpp \
		command/Nick.cpp \
		command/User.cpp \
		command/Join.cpp \
		command/Invite.cpp \
		command/Topic.cpp \
		command/Privmsg.cpp \
		command/Mode.cpp \
		command/Quit.cpp \
    	command/Ping.cpp \
		command/Kick.cpp \
		command/Part.cpp \
		command/Bot.cpp

FT_IRC = $(addprefix srcs/, $(SRCS))

OBJS = $(FT_IRC:.cpp=.o)
DEPS = $(FT_IRC:.cpp=.d)
-include $(DEPS)

%.o : %.cpp
	@ $(COMPILE.cpp) $(OUTPUT_OPTION) $<

$(NAME) : $(OBJS)
	@ $(LINK.cpp) $^ $(LOADLIBES) $(LDLIBS) -o $@

all : $(NAME)

clean :
	@ $(RM) $(OBJS) $(DEPS)

fclean : clean
	@ $(RM) $(NAME) $(DEPS)

re :
	@ $(MAKE) fclean
	@ $(MAKE) all

.PHONY : all clean fclean re