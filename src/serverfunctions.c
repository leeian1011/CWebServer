#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>

#include "httprequestfunctions.h"
#include "serverfunctions.h"

int initialize_server(void){
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(80);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    bind(serverSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress));
    listen(serverSocket, 1);

    int webSocket = accept(serverSocket, NULL, NULL);

    return webSocket;
}


int file_length(char *path){
    int fileLength = 0;
    char c;

    FILE *pathFile = fopen(path, "r");
    if(pathFile == NULL){
        return - 1;
    }

    while((c = fgetc(pathFile)) != EOF){
        fileLength++;
    }
    
    fclose(pathFile);

    return fileLength + 1;
}


char * pull_html_response(const char *path, char *htmlResponse){
    FILE *html = fopen(path, "r");
    if(html == NULL){
        return NULL;
    }

    fread(htmlResponse, strlen(htmlResponse), sizeof(char *), html);
        
    fclose(html);
    
    return htmlResponse;
}

