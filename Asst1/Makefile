all: test

test: memgrind.c
	gcc -Wall -Werror mymalloc.h
	gcc -Wall -Werror -c mymalloc.c
	gcc -Wall -Werror  memgrind.c mymalloc.c -o memgrind.o

clean:
	rm -rf memgrind.o
	rm -rf mymalloc.o


