#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <regex.h>
#include <stdbool.h>


#include "httpfunctions.h"
#include "serverfunctions.h"

// Accept only up to 8kb of data from a browser http request.
const int HTTP_REQUEST_BYTE_SIZE = 8192;
// Accept up to double the minimum size of a standard http method line.
const int HTTP_METHODLINE_BYTE_SIZE = 76;

//add a global variable to allow sourcing of different file files.
const char *INDEX = "page/index.file";
const char *ABOUT = "page/about.file";
const char *NOT_FOUND = "page/404.file";
// Accept up to double the minimum size (15) of path.
const int PATH_BYTE_SIZE = 45;

const char *requested_file(char *requestedUrl){
    if(strcasecmp(requestedUrl, "/") == 0){
        return INDEX;
    }else if(strcasecmp(requestedUrl, "/about") == 0){
        return ABOUT;
    } 

    return NOT_FOUND;
}


int main(void){
    int serverSocket = initialize_server();
    
    while(1){
    listen(serverSocket, 10);
    int socket = accept(serverSocket, NULL, NULL);
    HttpRequest *request = malloc(sizeof(HttpRequest)); 
    char *requestBuffer = malloc(HTTP_REQUEST_BYTE_SIZE); 
    char *httpMethodLine = malloc(HTTP_METHODLINE_BYTE_SIZE);
    char *path = NULL; 
    char *file = NULL; 
    char *httpResponse = NULL;
    size_t fileLength = 0;


    recv(socket, requestBuffer, HTTP_REQUEST_BYTE_SIZE, 0); 
    printf("%s\n\n", requestBuffer);
    parse_http_request(requestBuffer, httpMethodLine); 
    set_httprequest_fields(httpMethodLine, request);

    path = malloc(PATH_BYTE_SIZE);

    if(!is_icon_request(request->requesturl)){
        strcpy(path, request->requesturl);
    }else{
        strcpy(path, requested_file(request->requesturl)); 
    }

    fileLength = file_length(path); 
    if(fileLength == -1){
        printf("Could not get length of file file requested");
    }

    file = malloc(fileLength);
    pull_file(path, file, fileLength);
    printf("%s\n", file);

    generate_http_response(&httpResponse, path, file);
    send(socket, httpResponse, strlen(httpResponse), 0);
    shutdown(socket, 2);
    free(request);
    free(requestBuffer);
    free(httpMethodLine);
    free(file);
    free(path);
    free(httpResponse);
    }
    return 0;
}
