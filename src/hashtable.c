#include <stdio.h>
#include <string.h>

#include "hashtable.h"

HttpRequest parse_http_request(char *BrowserResponse){
    for(int i = 0; i < strlen(BrowserResponse); i++){
        if(strcmp(BrowserResponse + i, "\r\n") == 0){
            printf("Found a line");
        }
    }
    HttpRequest test;
    test.httpmethod = "Get";
    test.requesturl = "hehe";

    return test;
}

