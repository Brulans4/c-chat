CFLAGS=-std=c11 -pedantic -Wvla -Werror -Wall -D_DEFAULT_SOURCE


ALL= server client

all: clean $(ALL)

utils.o: utils.c utils.h
	cc $(CFLAGS) -c -g utils.c

server.o: server.c server.h utils.h properties.h
	cc $(CFLAGS) -c -g server.c

client.o: client.c client.h utils.h properties.h
	cc $(CFLAGS) -c -g client.c


server: server.o utils.o
	cc $(CFLAGS) -o server server.o utils.o

client: client.o utils.o 
	cc $(CFLAGS) -o client client.o utils.o


clean:
	rm -f $(ALL) *.o