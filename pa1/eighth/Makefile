all: first
first: first.c
	gcc -Wall -Werror -fsanitize=address -std=c11 eighth.c -o eighth
clean:
	rm -rf first
