all: first
first: first.c
	gcc -Wall -Werror -fsanitize=address -std=c11 fifth.c -o fifth
clean:
	rm -rf first
