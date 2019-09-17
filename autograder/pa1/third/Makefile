all: first
first: first.c
	gcc -Wall -Werror -fsanitize=address -std=c11 third.c -o third
clean:
	rm -rf first
