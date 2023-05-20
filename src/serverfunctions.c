#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <stdbool.h>
#include <regex.h>

#include "httpfunctions.h"
#include "serverfunctions.h"

int initialize_server(void){
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(80);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    bind(serverSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress));

    return serverSocket;
}


size_t file_length(char *path){
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


bool is_icon_request(char *requestedUrl){
   regex_t re;
   char *pattern = "(/favicon_io)";
   
   int regex = regcomp(&re, pattern, REG_EXTENDED);
   if(regex){
       printf("error compiling regex\n");
    }
   
   regex = regexec(&re, requestedUrl, 0, NULL, 0);
   if(regex == REG_NOMATCH){
       return false;
   }else{
       printf("pattern works\n");
       return true;
   }

    return false;
}


char *pull_file(const char *path, char *html, size_t htmlLength){
    FILE *htmlFile = fopen(path, "r");
    if(html == NULL){
        return NULL;
    }
    fread(html, htmlLength, sizeof(char *), htmlFile);
    fclose(htmlFile);
    
    return html;
}

