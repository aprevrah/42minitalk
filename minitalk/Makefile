CC = cc # compiler
CFLAGS = -Wall -Werror -Wextra
RM = rm -f

SOURCES = server.c client.c
OBJECTS = $(SOURCES:.c=.o)

NAME = server
C_NAME = client

all: libft $(NAME) $(C_NAME)
	
libft:
	make -C ./libft all

$(NAME): server.o libft/libft.a
	$(CC) $(CFLAGS) -o $@ $< -L./libft -lft
$(C_NAME): client.o libft/libft.a
	$(CC) $(CFLAGS) -o $@ $< -L./libft -lft

%.o: %.c
	$(CC) -c $(CFLAGS) $?

clean:
	make -C ./libft clean
	$(RM) $(OBJECTS)

fclean: clean
	make -C ./libft fclean
	$(RM) $(NAME) $(C_NAME)

re: fclean all

.PHONY: all libft clean fclean re