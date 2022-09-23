SRCS         =    init_socket.cpp \
					server.cpp \
					client.cpp \
					orders.cpp \
					#./orders/nickname.cpp \
					#./orders/username.cpp \
					#./orders/tools.cpp \

OBJS         =     ${SRCS:.cpp=.o}

CC             =     c++
CFLAGS        =     -Wall -Wextra -Werror -std=c++98 -g
RM            =     rm -f
NAME        =     ircserv

all:             ${NAME}

.cpp.o:
				${CC} ${CFLAGS} -c $< -o ${<:.cpp=.o}
				
$(NAME):         $(OBJS)
				${CC} $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJS):     server.hpp client.hpp

clean:
				${RM} ${OBJS}

fclean:         clean
				${RM} ${NAME}

re:             fclean all

.PHONY:            all clean fclean re