#ifndef SERVERFUNCTIONS_H
#define SERVERFUNCTIONS_H

#include <stdio.h>

#include "httprequestfunctions.h"

#define INDEX "page/index.html"
#define ABOUT "page/about.html" 
#define NOTFOUND "page/404.html"


int initialize_server(void);
int file_length(char *path);
char *pull_html_response(const char* path, char *htmlResponse); 
char *render_response(char *httpRequestUrl);
#endif
