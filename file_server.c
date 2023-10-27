/*
c socket file server
*/
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>

int main(int argc, char ** argv) {
    FILE *infile;
    size_t fileSize;
    int serverSocket, clientSocket;
    struct sockaddr_in address;
    int addrSize = sizeof(address);
    int yes = 0;

    int bindStatus, setsockoptStatus, listenStatus;

    infile = fopen("server.out", "rb");

    fseek(infile, 0, SEEK_END);

    fileSize = ftell(infile);

    printf("The file size is: %ld\n", fileSize);
    rewind(infile);

    char fileBuffer[fileSize];

    // Maybe reading the file.....
    fread(fileBuffer, fileSize, fileSize, infile);

    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_family = AF_INET;
    address.sin_port = htons(1234);

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    setsockoptStatus = setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));
    bindStatus = bind(serverSocket, (struct sockaddr *)&address, addrSize);

    listenStatus = listen(serverSocket, 5);

    printf("setsockoptStatus: %d\n", setsockoptStatus);
    printf("bindStatus: %d\n", bindStatus);
    printf("listenStatus: %d\n", listenStatus);

    clientSocket = accept(serverSocket, (struct sockaddr *) &address, (socklen_t *)&addrSize);
    printf("clientSocket: %d\n", clientSocket);

    char buffer[1024];
    memset(buffer, 0, strlen(buffer));
    sprintf(buffer, "%ld", fileSize);
    send(clientSocket, buffer, strlen(buffer), 0);
    
    memset(buffer, 0, strlen(buffer));
    recv(clientSocket, buffer, 1024, 0);

    printf("Client ready to receive file\n");
    memset(buffer, 0, strlen(buffer));

    send(clientSocket, fileBuffer, fileSize, 0);

    recv(clientSocket, buffer, 1024, 0);
    printf("Client says: %s\n", buffer);
    memset(buffer, 0, strlen(buffer));
    
    // while(1) {

    // }
    close(serverSocket);
    close(infile);
    return 0;
}