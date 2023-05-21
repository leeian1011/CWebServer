#include <stdlib.h>
#include <string.h>

#include "httpfunctions.h"
#include "serverfunctions.h"

/* Parses HTTP Request Method line into a string and returns it */
char *parse_http_request(char *BrowserResponse, char *parseHolder){
    int lengthOfBrowserResponse = strlen(BrowserResponse);
    
    /* The for loop iterates over the entire HTTPRequest until it reaches the first '\r',
     * a second for loop is used to iterate up to the first '\r' and store the values into the parseHolder parameter */

    for(int i = 0; i < lengthOfBrowserResponse; i++){
        if(BrowserResponse[i] == '\r'){
            for(int j = 0; j < i; j++){
                parseHolder[j] = BrowserResponse[j];
            }
            parseHolder[i] = '\0';
            break;
        }
    }
    return parseHolder;
}


unsigned char *generate_http_response(unsigned char **httpResponse, char *path, unsigned char *file, size_t *fileLength){
    char *okResponse = "HTTP\\1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
    char *errorResponse = "HTTP\\1.1 404 Not Found\r\nContent-Type: text/html\r\n\r\n";
    char *iconResponse = "HTTP\\1.1 200 OK\r\nContent-Type: image/x-icon\r\n\r\n";
    char *responseCode = NULL;
    size_t tmpfileLength = *fileLength;
    size_t responseCodeLength = 0;
   printf("variables initialized properly"); 
    if(is_icon_request(path)){
        printf("icon success path = %s\n", path);
        responseCodeLength = strlen(iconResponse);
        responseCode = iconResponse;
    }else if(strcasecmp(path, "page/404.html") == 0){
        responseCodeLength = strlen(errorResponse);
        responseCode = errorResponse;
    }else{
        printf("icon fail path = %s\n", path);
        responseCodeLength = strlen(okResponse);
        responseCode = okResponse;
    }
   printf("passed icon testing\n\n"); 
    *fileLength += responseCodeLength;
    *httpResponse = malloc(*fileLength + 10);
    printf("length == %lu\n\n", *fileLength);
    printf("malloc httpResponse successful\n");

    memcpy(*httpResponse, responseCode, responseCodeLength);
    memcpy(*httpResponse + responseCodeLength, file, tmpfileLength);
    return *httpResponse;
}


HttpRequest *set_httprequest_fields(char *httpMethodLine, HttpRequest *request){
    request->httpmethod = strtok(httpMethodLine, " ");
    request->requesturl = strtok(NULL, " ");
    
    return request;
}
