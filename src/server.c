#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

#include "httpfunctions.h"
#include "serverfunctions.h"

// Accept only up to 8kb of data from a browser http request.
const int HTTP_REQUEST_BYTE_SIZE = 8192;
// Accept up to double the minimum size of a standard http method line.
const int HTTP_METHODLINE_BYTE_SIZE = 32;

//add a global variable to allow sourcing of different html files.
const char *INDEX = "page/index.html";
const char *ABOUT = "page/about.html";
const char *NOT_FOUND = "page/404.html";
// Accept up to double the minimum size (15) of path.
const int PATH_BYTE_SIZE = 30;

const char *requested_html(char *requestedUrl){
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
    char *html = NULL; 
    char *httpResponse = NULL;
    int htmlLength = 0;


    recv(socket, requestBuffer, HTTP_REQUEST_BYTE_SIZE, 0); 
    printf("%s\n\n", requestBuffer);
    parse_http_request(requestBuffer, httpMethodLine); 
    set_httprequest_fields(httpMethodLine, request);

    path = malloc(PATH_BYTE_SIZE);
    strcpy(path, requested_html(request->requesturl));    

    htmlLength = file_length(path); 
    if(htmlLength == -1){
        printf("Could not get length of html file requested");
    }

    html = malloc(htmlLength);
    pull_html(path, html, htmlLength);
    printf("%s\n", html);

    generate_http_response(httpResponse, path, html);
    send(socket, html, htmlLength, 0);
    shutdown(socket, 2);

    free(request);
    free(requestBuffer);
    free(httpMethodLine);
    free(html);
    free(path);
    }
    return 0;
}
