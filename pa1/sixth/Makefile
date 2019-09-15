all: first
first: first.c
	gcc -Wall -Werror -fsanitize=address -std=c11 sixth.c -o sixth
clean:
	rm -rf first
