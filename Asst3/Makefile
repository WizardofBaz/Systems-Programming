all: WTFclient.c WTFserver.c
	gcc -pthread -O -g -o WTFserver WTFserver.c
	gcc -lcrypto -O -g -o WTFclient WTFclient.c

clean:
	rm -rf WTFclient.o
	rm -rf WTFserver.o


