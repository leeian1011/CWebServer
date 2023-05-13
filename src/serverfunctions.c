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

int file_length(char *url){
    int fileLength = 0;
    char *path = NULL;
    char c;

    printf("--%s-- \n", url);

    if(strcasecmp(url, "/") == 0){
        path = INDEX; 
    }else if(strcasecmp(url, "/about") == 0){
        path = ABOUT;
    }else{
        path = NOTFOUND;
    }
    
    printf("Attempting to open path to %s\n", path);

    FILE *pathFile = fopen(path, "r");
    if(pathFile == NULL){
        return - 1;
    }

    while((c = fgetc(pathFile)) != EOF){
        fileLength++;
    }
    printf("%s", path); 
    rewind(pathFile);
    fclose(pathFile);

    return fileLength;
}


char * pull_html_response(char *url, const char *requestedHtml, char *htmlResponse){
    int filelength = 0;
    char c;
    FILE *html = fopen(requestedHtml, "r");
    if(html == NULL){
        return NULL;
    }
    
    fread(htmlResponse, filelength + 1, 1, html);

    fclose(html);
    
    return htmlResponse;
}

