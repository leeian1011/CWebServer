#include <stdio.h>
#include <string.h>

#include "hashtable.h"

HttpRequest parse_http_request(char *BrowserResponse){
    int lengthOfBrowserResponse = strlen(BrowserResponse);
    char tmp[50];

    /* The for loop iterates over the entire HTTPRequest until it gets the first '\r',
     * it then parses out and stores in a temporary char array the HTTP method line */

    for(int i = 0; i < lengthOfBrowserResponse; i++){
        if(BrowserResponse[i] == '\r'){
            for(int j = 0; j < i; j++){
                tmp[j] = BrowserResponse[j];
            }
            tmp[i] = '\0';
            break;
        }
    }
    
    /* Initialize the HttpRequest struct and use strtok to break up the 
     * request method and request url */
      
    HttpRequest request;
    request.requesturl = strtok(tmp, " ");
    request.httpmethod = strtok(NULL, " ");

    return request;
}

