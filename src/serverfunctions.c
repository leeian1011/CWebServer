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

bool is_icon_request(char *path){
    regex_t re;
    int regex;

    regex = regcomp(&re, "(favicon)", 0);
    
    if(regex != 0){
        printf("Regex compilation failed\n\n");
        return false;
    }

    printf("Currently Matching request for icon request");
    regex = regexec(&re, path, 0, NULL, REG_EXTENDED);
    if(regex == REG_NOMATCH){
        return false;
    }else if(regex == 0){
        return true;
    }

    return true;
}
    
size_t file_length(char *path){
    int fileLength = 0;
    FILE *pathFile = fopen(path, "rb");
    if(pathFile == NULL){
        return - 1;
    }
    
    fseek(pathFile, 0, SEEK_END);
    fileLength = ftell(pathFile);
    rewind(pathFile);
    fclose(pathFile);

    return fileLength;
}



unsigned char *pull_file(char *path, unsigned char *file, size_t fileLength){
    FILE *readFile = fopen(path, "rb");
    if(readFile == NULL){
        return NULL;
    }

    fread(file, sizeof(char), fileLength, readFile);
    fclose(readFile);

    return file;
}

