all: test

test: memgrind.c
gcc -Wall -Werror mymalloc.h
gcc -Wall -Werror mymalloc.c
gcc -Wall -Werror -o memgrind

clean:
rm -rf memgrind

