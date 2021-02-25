CC = clang++
CFLAGS = -g3 -fsanitize=address
NAME = ircserv
INCLUDE = -I ./include/

# SSL = -L /usr/local/Cellar/openssl@1.1/1.1.1i/lib -lssl -lcrypto
# SSLI = -I/usr/local/Cellar/openssl@1.1/1.1.1i/include/openssl/

SRC = main.cpp utils.cpp localServerInit.cpp localServerConn.cpp RemoteServer.cpp User.cpp Message.cpp Transmit.cpp \
CommandInit.cpp command.cpp
SRC_DIR = ./src/
SRCS = $(addprefix $(SRC_DIR), $(SRC))
OBJS = $(SRCS:%.cpp=%.o)

# SRC_COM = 


# SRC_COM_DIR = ./src/command
SRCS_COM = $(addprefix $(SRC_COM_DIR), $(SRC_COM))
OBJS_COM = $(SRCS_COM:%.cpp=%.o)

# SRC_RE = registerReplies.cpp commandResponse.cpp errorResponse.cpp
# SRC_RE_DIR = ./src/responseHandler/
# SRCS_RE = $(addprefix $(SRC_RE_DIR), $(SRC_RE))
# OBJS_RE = $(SRCS_RE:%.cpp=%.o)

all : $(NAME)

# $(NAME) : $(OBJS) $(OBJS_COM) $(OBJS_RE)
# 	$(CC) $(CFLAGS) $(INCLUDE) $(SSLI) $(SSL) $(OBJS) $(OBJS_COM) $(OBJS_RE) -o $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDE) $(OBJS) -o $(NAME)

.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $<

debug:
	$(CC) $(CFLASG) $(INCLUDE) -D DEBUG=1 $(SRCS) -o $(NAME)

clean:
	rm -rf $(OBJS) $(OBJS_COM) $(OBJS_RE)

fclean : clean
	rm -rf $(NAME)

re: fclean all

.PHONY: clean fclean all re
