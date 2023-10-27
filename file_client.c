/*
c socket file client
*/
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>

int main(int argc, char ** argv) {
    int newSocket;
    struct sockaddr_in address;
    int addrSize = sizeof(address);

    inet_pton(AF_INET, "127.0.0.1", &(address.sin_addr));
    address.sin_family = AF_INET;
    address.sin_port = htons(1234);

    newSocket = socket(AF_INET, SOCK_STREAM, 0);
    connect(newSocket, (struct sockaddr *) &address, addrSize);

    char buffer[1024];
    size_t fileSize;
    memset(buffer, 0, 1024);

    recv(newSocket, buffer, 1024, 0);

    printf("Received file size from server: %s\n", buffer);
    fileSize = atol(buffer);
    char fileBuffer[fileSize];
    memset(buffer, 0, strlen(buffer));

    sprintf(buffer, "send file");
    send(newSocket, buffer, strlen(buffer), 0);
    memset(buffer, 0, strlen(buffer));

    size_t offset = 0;
    size_t recvBytes = 0;

    while(offset < fileSize) {
        recvBytes = recv(newSocket, buffer, 1024, 0);
        sprintf(fileBuffer, buffer);
        memset(buffer, 0, strlen(buffer));
        offset += recvBytes;
    }

    sprintf(buffer, "Received: %ld\n", offset);
    send(newSocket, buffer, strlen(buffer), 0);

    return 0;
}