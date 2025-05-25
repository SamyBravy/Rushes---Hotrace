NAME=hotrace

CC=gcc
CFLAGS=-Wall -Wextra -Werror -Wno-unused-result -O3 -I.

SRC = ./expand_hashtable.c \
	./get_next_line.c \
	./hashing.c \
	./main.c \
	./utils.c


all: $(NAME)

$(NAME): $(SRC)
	$(CC) $(CFLAGS) -o $(NAME) $(SRC)
	echo "\e[32m$(NAME) compiled successfully.\e[0m"

clean:
	rm -f $(NAME)
	echo "\e[91m$(NAME) program removed.\e[0m"

fclean: clean

re: fclean all

.PHONY: all clean fclean re
.SILENT: