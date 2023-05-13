#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdio.h>

typedef struct HttpRequest{
    char *httpmethod;
    char *requesturl;
}
HttpRequest;

char *parse_http_request(char *BrowserResponse, char *parseHolder); 
HttpRequest *set_httprequest_fields(char *httpMethodLine, HttpRequest *request);
#endif
