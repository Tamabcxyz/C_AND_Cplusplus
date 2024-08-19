CC = gcc
CFLAGS = -Wall -save-temps
LIBS = 

all: server client

client: client.c
	$(CC) $(CFLAGS) client.c -o client $(LIBS)

server: server.c
	$(CC) $(CFLAGS) server.c -o server $(LIBS)

clean:
	rm -rf client server
	rm -rf *.i *.o *.s