all: first
first: first.c
	gcc -Wall -Werror -fsanitize=address -std=c11 seventh.c -o seventh
clean:
	rm -rf first
