#include <stdlib.h>
#include <string.h>

#include "httprequestfunctions.h"

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

HttpRequest *set_httprequest_fields(char *httpMethodLine, HttpRequest *request){
    request->httpmethod = strtok(httpMethodLine, " ");
    request->requesturl = strtok(NULL, " ");

    return request;
}
