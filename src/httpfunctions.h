#ifndef HTTPFUNCTIONS_H 
#define HTTPFUNCTIONS_H 

#include <stdio.h>

typedef struct HttpRequest{
    char *httpmethod;
    char *requesturl;
}
HttpRequest;

char *parse_http_request(char *BrowserResponse, char *parseHolder); 
unsigned char *generate_http_response(unsigned char **httpResponse, char *path, unsigned char *file, size_t *fileLength);
HttpRequest *set_httprequest_fields(char *httpMethodLine, HttpRequest *request);
#endif
