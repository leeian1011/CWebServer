#ifndef HTTPFUNCTIONS_H 
#define HTTPFUNCTIONS_H 

#include <stdio.h>

typedef struct HttpRequest{
    char *httpmethod;
    char *requesturl;
}
HttpRequest;

char *parse_http_request(char *BrowserResponse, char *parseHolder); 
char *generate_http_response(char *httpResponse, char *htmlResponse);
HttpRequest *set_httprequest_fields(char *httpMethodLine, HttpRequest *request);
#endif
