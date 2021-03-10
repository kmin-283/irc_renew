CC = clang++
CFLAGS = -g3 -fsanitize=address
NAME = ircserv

INCLUDE = -I ./include/

SSLI = -I /usr/include/openssl/

SRC = main.cpp utils.cpp LocalServerInit.cpp LocalServerConn.cpp \
Executer.cpp ExecuterInit.cpp RemoteServer.cpp Channel.cpp User.cpp Message.cpp \
CommandInit.cpp Command.cpp ReplyInit.cpp Reply.cpp ErrReply.cpp Variables.cpp \
/NICK/nickHandler.cpp
SRC_DIR = ./src/
SRCS = $(addprefix $(SRC_DIR), $(SRC))
OBJS = $(SRCS:%.cpp=%.o)

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDE) $(OBJS) -o $(NAME) $(SSLI) -lssl -lcrypto

.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $<

debug:
	$(CC) $(CFLASG) $(INCLUDE) -D DEBUG=1 $(SRCS) -o $(NAME) $(SSLI) -lssl -lcrypto

clean:
	rm -rf $(OBJS) $(OBJS_COM) $(OBJS_RE)

fclean : clean
	rm -rf $(NAME)

re: fclean all

.PHONY: clean fclean all re
