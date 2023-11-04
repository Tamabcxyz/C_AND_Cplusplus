CC = g++
CFLAGS = -Wall -save-temps
LIBS = -lzmq

all: server client

client: client.cpp
	$(CC) $(CFLAGS) client.cpp -o client $(LIBS)

server: server.cpp
	$(CC) $(CFLAGS) server.cpp -o server $(LIBS)

clean:
	rm -rf client server
	rm -rf *.ii *.o *.s