NAME=hotrace

CC=cc
CFLAGS=-Wall -Wextra -Werror -O3 -I.

HASH_TABLE_SIZE ?= 333337

CFLAGS += -DHASH_TABLE_SIZE=$(HASH_TABLE_SIZE)

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
gen:
	@rm -f gen test.txt
	@echo "Generating files..."
	cc gen.c -o gen
	./gen > test.txt
	@echo "Test file generated as test.txt"

# Added prof target as an alias to profile
prof: profile

exec: gen
	@echo "Executing the program..."
	./$(NAME) < test.txt

profile: CFLAGS += -pg
profile: LDFLAGS += -pg
profile: re

gprof-report: 
	@if [ -f gmon.out ]; then \
		gprof -lp -v $(NAME) > profile_report.txt; \
		echo "Detailed profile report generated as profile_report.txt"; \
	else \
		echo "Error: gmon.out not found. Run the program with 'make profile' first."; \
	fi

gprof-visual: gprof-report 
	@if [ -f $(HOME)/.local/bin/gprof2dot ]; then \
		$(HOME)/.local/bin/gprof2dot -f prof profile_report.txt | dot -Tpng -o profile.png; \
		echo "Visual profile generated as profile.png"; \
	else \
		echo "Please install gprof2dot with: pip3 install --user gprof2dot"; \
		exit 1; \
	fi

# Complete profiling workflow in a single command
profile-all: profile
	@echo "Generating test data..."
	@rm -f gen test.txt
	cc gen.c -o gen
	./gen > test.txt
	@echo "Running program with profiling enabled..."
	./$(NAME) < test.txt
	@echo "Generating profiling report..."
	gprof -lb $(NAME) > profile_report.txt
	@echo "Profile report generated as profile_report.txt"
	@if [ -f $(HOME)/.local/bin/gprof2dot ]; then \
		$(HOME)/.local/bin/gprof2dot -f prof profile_report.txt | dot -Tpng -o profile.png && \
		echo "Visual profile generated as profile.png"; \
	fi
	@echo "Profiling complete!"
.PHONY: all clean fclean re
.SILENT: