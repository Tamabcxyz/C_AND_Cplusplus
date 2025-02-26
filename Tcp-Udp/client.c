#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    struct sockaddr_in address;

    // create socket
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if(fd==-1){
        perror("Cannot create socket\n");
        exit(1);
    }
    // set server address
    address.sin_family = AF_INET;
    address.sin_port = htons(8080);

    // convert ipv4 and ipv6 from text to binary form
    if(inet_pton(AF_INET, "127.0.0.1", &address.sin_addr)==-1){
        perror("Cannot convert\n");
        exit(1);
    }
    // connect
    if(connect(fd, (struct sockaddr *)&address, sizeof(address))==-1){
        perror("Cannot connect\n");
        exit(1);
    }
    char buffer[1024] = {0};
    const char *hello = "Hello from client";
    // Sending a message to the server
    send(fd, hello, strlen(hello), 0);

    // Reading the response from the server
    read(fd, buffer, 1024);
    printf("Message from server: %s", buffer);

    // Closing the socket
    close(fd);
    return 0;
}
