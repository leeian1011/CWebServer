#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>

#include "httprequestfunctions.h"
#include "serverfunctions.h"

// Accept only up to 8kb of data from a browser http request.
const int HTTP_REQUEST_BYTE_SIZE = 8192;
// Accept up to double the minimum size of a standard http method line.
const int HTTP_METHODLINE_BYTE_SIZE = 32;


char *requested_html(char *url){
    if(strcasecmp(url, "/") == 0){
        return INDEX;
    }else if(strcasecmp(url, "/about") == 0){
        return ABOUT;
    }

    return NOTFOUND;
}

int main(void){
    HttpRequest *request = malloc(sizeof(HttpRequest));
    char *requestBuffer = malloc(HTTP_REQUEST_BYTE_SIZE);
    char *httpMethodLine = malloc(HTTP_METHODLINE_BYTE_SIZE);
    char *path = NULL;
    char *htmlResponse = NULL;
    int htmlResponseLength;

    int socket = initialize_server();

    recv(socket, requestBuffer, HTTP_REQUEST_BYTE_SIZE, 0);
    parse_http_request(requestBuffer, httpMethodLine);
    set_httprequest_fields(httpMethodLine, request);
    
    path = requested_html(request->requesturl);
    
    htmlResponseLength = file_length(path);
    if(htmlResponseLength == -1){
        printf("Could not get length of html file requested");
        return -1;
    }
    
    htmlResponse = malloc(htmlResponseLength);


    return 0;
}
