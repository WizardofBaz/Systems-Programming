all: test

test: memgrind.c
	gcc -Wall -Werror mymalloc.h
	gcc -Wall -Werror -c -g mymalloc.c
	gcc -g -Wall -Werror  memgrind.c mymalloc.c -o memgrind

clean:
	rm -rf memgrind.o
	rm -rf mymalloc.o

