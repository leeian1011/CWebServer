#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

#include "hashtable.h"

HttpRequest parse_http_request(char *BrowserResponse);

int initializeServer(void){
    int ServerSocket = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in ServerAddress;
    ServerAddress.sin_port = htons(80);
    ServerAddress.sin_family = AF_INET;
    ServerAddress.sin_addr.s_addr = INADDR_ANY;

    bind(ServerSocket, (struct sockaddr*) &ServerAddress, sizeof(ServerAddress));
    listen(ServerSocket, 1);

    int ClientSocket = accept(ServerSocket, NULL, NULL);
    return ClientSocket;
}

int main(void){
    char *buffer = malloc(5000);
    int Socket = initializeServer();

    recv(Socket, buffer, 5000, 0);
    
    HttpRequest request = parse_http_request(buffer);

    free(buffer);
    return 0;
}
