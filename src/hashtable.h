#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdio.h>

typedef struct HttpRequest{
    char *httpmethod;
    char *requesturl;
}
HttpRequest;

HttpRequest parse_http_request(char *BrowserResponse); 

#endif
