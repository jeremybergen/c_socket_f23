/*
C Socket Server
*/
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>

//int main(int argc, char *argv[])
int main(int argc, char **argv) {
    int serverSocket;
    // int serverSocket2;
    int setsockoptStatus;
    int bindStatus;
    int listenStatus;
    int newSocket;
    // struct sockaddr_in address;
    struct addrinfo hints, *res;
    struct sockaddr_storage address;
    int addrSize = sizeof(address);
    int yes = 1;

    char buffer[1024] = {0};


    FILE    *infile;
    char    *fbuffer;
    long    numbytes;

    // old way
    // memset(&address, 0, sizeof(address));
    // address.sin_family = AF_INET;
    // address.sin_addr.s_addr = INADDR_ANY;
    // address.sin_port = htons(1234);

    // new way
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    getaddrinfo(NULL, "1234", &hints, &res);

    serverSocket = socket(res->ai_family, res->ai_socktype, 0);
    // serverSocket2 = socket(AF_INET, SOCK_STREAM, 0);

    printf("serverSocket: %d\n", serverSocket);
    // printf("serverSocket2: %d\n", serverSocket2);

    setsockoptStatus = setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));
    printf("setsockoptStatus: %d\n", setsockoptStatus);

    bindStatus = bind(serverSocket, res->ai_addr, res->ai_addrlen);
    printf("bindStatus: %d\n", bindStatus);

    // listenStatus = listen(serverSocket, 1);
    // printf("listenStatus: %d\n", listenStatus);

    // newSocket = accept(serverSocket, (struct sockaddr *)&address, (socklen_t *)&addrSize);
    // printf("newSocket: %d\n", newSocket);

    // Echo....echo
    // while(1) {
    //     int recvBytes = recv(newSocket, buffer, 1024, 0);
    //     printf("Received: %s\n", buffer);

    //     if(strncmp(buffer, "quit", 4) == 0) {
    //         close(newSocket);
    //         break;
    //     }

    //     send(newSocket, buffer, strlen(buffer), 0);
    //     memset(&buffer, 0, sizeof(buffer));
    // }

    // file transfer
    infile = fopen("server.out", "r");
    /* quit if the file does not exist */
    if(infile == NULL)
        return 1;
    
    /* Get the number of bytes */
    fseek(infile, 0L, SEEK_END);
    numbytes = ftell(infile);
    
    /* reset the file position indicator to 
    the beginning of the file */
    fseek(infile, 0L, SEEK_SET);	
    
    /* grab sufficient memory for the 
    buffer to hold the text */
    fbuffer = (char*)calloc(numbytes, sizeof(char));
    
    /* memory error */
    if(fbuffer == NULL)
        return 1;
    
    /* copy all the text into the buffer */
    fread(fbuffer, sizeof(char), numbytes, infile);
    fclose(infile);
    printf("File Size: %ld\n", numbytes);
    
    /* confirm we have read the file by
    outputing it to the console */
    // printf("The file called test.dat contains this text\n\n%s", buffer);
    
    /* free the memory we used for the buffer */
    // free(buffer);

    // while(1) {

    // }
    // printf("Hello World\n");
    // close(newSocket);
    close(serverSocket);
    return 0;
}