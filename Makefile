NAME=hotrace

CC=gcc
CFLAGS=-Wall -Wextra -Werror -Wno-unused-result -O3 -I.

# HASH_TABLE_SIZE ?= 333337
# CFLAGS += -DHASH_TABLE_SIZE=$(HASH_TABLE_SIZE)

SRC = ./get_next_line.c \
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


pre-profile: CFLAGS += -pg
pre-profile: LDFLAGS += -pg
pre-profile: re

# Complete profiling workflow in a single command
profile: pre-profile
	@echo "Generating test data..."
	@rm -f gen test_file
	cc gen.c -o gen
	./gen > test_file
	@echo "Running program with profiling enabled..."
	./$(NAME) < test_file
	@echo "Generating profiling report..."
	gprof -lb $(NAME) > profile_report.txt
	@echo "Profile report generated as profile_report.txt"
# @if [ -f $(HOME)/.local/bin/gprof2dot ]; then \
# 	$(HOME)/.local/bin/gprof2dot -f prof profile_report.txt | dot -Tpng -o profile.png && \
# 	echo "Visual profile generated as profile.png"; \
# fi
	@echo "Profiling complete!"
.PHONY: all clean fclean re
.SILENT: