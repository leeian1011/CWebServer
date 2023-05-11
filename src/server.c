#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>

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

char *grab_route_file(char *requesturl){
    char* buffer = NULL;
    if(strcmp(requesturl, "/") == 0){
        FILE *index = fopen("page/index.html", "r");
        if(index == NULL){
            return "woops";
        }
        char c;
        int filelength = 0;
        while((c = fgetc(index)) != EOF){
            filelength++;
        }

        rewind(index);
        
        buffer = malloc(filelength + 1);

        fread(buffer, filelength, 1, index);

        printf("%s", buffer);
        
        return buffer;
    }if(strcmp(requesturl, "/about") == 0){
        FILE *about = fopen("page/about.html", "r");
        if(about == NULL){
            return "woops";
        }
        char c;
        int filelength = 0;
        while((c = fgetc(about)) != EOF){
            filelength++;
        }

        rewind(about);
        
        buffer = malloc(filelength + 1);

        fread(buffer, filelength, 1, about);

        printf("%s", buffer);
        
        return buffer;
    }
    return "<p> haha </p>";
}

int main(void){
    char *buffer = malloc(5000);
    int Socket = initializeServer();

    recv(Socket, buffer, 5000, 0);
    
    HttpRequest request = parse_http_request(buffer);
    char *tmp = grab_route_file(request.requesturl);   
    
    send(Socket, tmp, 5000, 0);
    free(buffer);
    return 0;
}
