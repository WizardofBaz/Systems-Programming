all: test

test: memgrind.c
  gcc -Wall -Werror mymalloc.h
  gcc -Wall -Werror mymalloc.c
  gcc -Wall -Werror memgrind.c -o memgrind.o

clean:
  rm -rf memgrind.o

