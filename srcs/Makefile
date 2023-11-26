.DEFAULT_GOAL=all

CXX = c++
CXXFLAGS =  -Wall -Wextra -Werror -std=c++98 -MMD -MP
RM = rm -rf
NAME = ircserv
SRCS = main.cpp \
		Command.cpp \
		Server.cpp \
		UserInfo.cpp \
		Pass.cpp \
		Message.cpp \
		Nick.cpp

OBJS = $(SRCS:.cpp=.o)
DEPS = $(SRCS:.cpp=.d)
-include $(DEPS)

%.o : %.cpp
	$(COMPILE.cpp) $(OUTPUT_OPTION) $<


$(NAME) : $(OBJS)
	$(LINK.cpp) $^ $(LOADLIBES) $(LDLIBS) -o $@

all : $(NAME)

clean :
		$(RM) $(OBJS) $(DEPS)

fclean : clean
		$(RM) $(NAME) $(DEPS)
re :
	$(MAKE) fclean
	$(MAKE) all

.PHONY : all clean fclean re