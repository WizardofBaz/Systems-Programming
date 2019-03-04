all: test
//this file should be good i dont think further changes will be needed
test: memgrind.c
  gcc -Wall -Werror mymalloc.h
  gcc -Wall -Werror mymalloc.c
  gcc -Wall -Werror memgrind.c -o memgrind.o

clean:
  rm -rf memgrind.o

