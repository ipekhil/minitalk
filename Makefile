NAME_SERVER = server
NAME_CLIENT = client

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS_SERVER = server.c
SRCS_CLIENT = client.c

OBJS_SERVER = server.o
OBJS_CLIENT = client.o

RM = rm -f

all: $(NAME_SERVER) $(NAME_CLIENT)

$(NAME_SERVER): $(OBJS_SERVER)
	$(CC) $(CFLAGS) -o $(NAME_SERVER) $(OBJS_SERVER)

$(NAME_CLIENT): $(OBJS_CLIENT)
	$(CC) $(CFLAGS) -o $(NAME_CLIENT) $(OBJS_CLIENT)

server.o: server.c
	$(CC) $(CFLAGS) -c server.c -o server.o

client.o: client.c
	$(CC) $(CFLAGS) -c client.c -o client.o

clean:
	$(RM) $(OBJS_SERVER) $(OBJS_CLIENT)

fclean: clean
	$(RM) $(NAME_SERVER) $(NAME_CLIENT)

re: fclean all

.PHONY: all clean fclean re
