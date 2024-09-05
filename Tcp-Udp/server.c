#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int opt = 1;
    struct sockaddr_in address;
    // create socket
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if(fd==-1){
        perror("Cannot create socket\n");
        exit(1);
    }
    // set socketopt
    if(setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1){
        perror("Cannot set socket option\n");
        exit(1);
    }
    // set server address
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);
    // bind
    if(bind(fd, (struct sockaddr *)&address, sizeof(address)) == -1){
        perror("Binding failed\n");
        exit(1);
    }
    // listen
    if(listen(fd, 3)==-1){
        perror("Listen failed\n");
        exit(1);
    }
    // accept connection
    int newSocket;
    int addrlen = sizeof(address);
    if((newSocket = accept(fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))==-1){
        perror("Cannot acept socket\n");
        exit(1);
    }
    // send and receive data
    const char *response = "Hello from server";
    char buffer[1024] = {0};
    read(newSocket, buffer, 1024);
    printf("Data client: %s", buffer);

    send(newSocket, response, strlen(response), 0);

    close(fd);
    close(newSocket);
    return 0;
}