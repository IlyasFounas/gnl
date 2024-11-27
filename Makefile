NAME    =   gnl.a
SRC     =   get_next_line.c get_next_line_utils.c
OBJ     =   $(SRC:.c=.o)
CFLAGS  =   -Wall -Wextra -Werror -D BUFFER_SIZE=100
CC      =   cc

$(NAME): $(OBJ)
	ar -rcs $(NAME) $(OBJ)

%.o: %.c get_next_line.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

all: $(NAME)

.PHONY: all clean fclean re
