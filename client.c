/*
Client socket code
*/
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char **argv) {
    int clientSocket;
    int connectStatus;
    struct sockaddr_in remoteAddr;

    memset(&remoteAddr, 0, sizeof(remoteAddr));
    remoteAddr.sin_family = AF_INET;
    // remoteAddr.sin_addr.s_addr = INADDR_ANY;
    inet_pton(AF_INET, "127.0.0.1", &(remoteAddr.sin_addr));
    remoteAddr.sin_port = htons(1234);

    clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    connectStatus = connect(clientSocket, (struct sockaddr *)&remoteAddr, sizeof(remoteAddr));

    char buffer[1024] = {0};
    while(1) {
        read(0, buffer, 1024);
        printf("buffer: %s\n", buffer);
        send(clientSocket, buffer, strlen(buffer), 0);
        if(strncmp(buffer, "quit", 4) == 0) {
            break;
        }
        memset(buffer, 0, strlen(buffer));

        recv(clientSocket, buffer, 1024, 0);
        printf("Received from server: %s\n", buffer);
        memset(buffer, 0, strlen(buffer));

    }

    close(clientSocket);

    return 0;
}