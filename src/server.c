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
const char *INDEX = "page/index.html";
const char *ABOUT = "page/about.html";
const char *NOT_FOUND = "page/404.html";
const char *ICON = "favicon.ico";
// Accept up to double the minimum size (15) of path.

const char *requested_file(char *requestedUrl){
    if(strcasecmp(requestedUrl, "/") == 0){
        return INDEX;
    }else if(strcasecmp(requestedUrl, "/about") == 0){
        return ABOUT;
    }else if(strcasecmp(requestedUrl, "/favicon.ico") == 0){
        return ICON;
    }

    return NOT_FOUND;
}


int main(void){
    int serverSocket = initialize_server();
    
    while(1){
    listen(serverSocket, 10);
    int socket = accept(serverSocket, NULL, NULL);
    HttpRequest request;
    char *requestBuffer = malloc(HTTP_REQUEST_BYTE_SIZE); 
    char *httpMethodLine = malloc(HTTP_METHODLINE_BYTE_SIZE);
    char *path = NULL; 
    unsigned char *file = NULL; 
    unsigned char *httpResponse = NULL;
    size_t fileLength = 0;


    recv(socket, requestBuffer, HTTP_REQUEST_BYTE_SIZE, 0);
    printf("Browser Request\n-------------\n%s\n", requestBuffer);

    parse_http_request(requestBuffer, httpMethodLine);
    printf("Http Method Line\n-------------\n%s\n", httpMethodLine);

    set_httprequest_fields(httpMethodLine, &request);
    printf("Request Fields\n-------------\n->requesturl : %s\n->httpmethod : %s\n\n", request.requesturl, request.httpmethod);

    path = malloc(strlen(request.requesturl));
    strcpy(path, requested_file(request.requesturl)); 
    printf("Path set to\n-------------\n%s\n\n", path);

    fileLength = file_length(path); 
    if(fileLength == -1){
        printf("Could not get length of file file requested");
    }
    
    file = malloc(fileLength);
    pull_file(path, file, fileLength);
    printf("File read\n-----------\n%s\n", file);

    printf("length byte %lu\n", fileLength);
    generate_http_response(&httpResponse, path, file, &fileLength);

    send(socket, httpResponse, fileLength, 0);
    shutdown(socket, 2);


    printf("MEMORY ADDRESS\n----------\n");
    printf("%p\n", requestBuffer);
    printf("%p\n", httpMethodLine);
    printf("%p\n", file);
    printf("%p\n", path);
    printf("%p\n", httpResponse);

    free(httpResponse);
    free(requestBuffer);
    free(httpMethodLine);
    free(file);
    free(path);
    }
    return 0;
}
