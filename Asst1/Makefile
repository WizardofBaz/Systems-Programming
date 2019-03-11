all: test

test: memgrind.c
	gcc -Wall -Werror -c -g -o mymalloc.o mymalloc.c
	gcc -g -Wall -Werror  memgrind.c mymalloc.o -o memgrind

clean:
	rm -rf memgrind.o
	rm -rf mymalloc.o



