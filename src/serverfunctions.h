#ifndef SERVERFUNCTIONS_H
#define SERVERFUNCTIONS_H

#include "httprequestfunctions.h"

int initialize_server(void);
int file_length(char *path);
char *pull_html_response(const char* path, char *htmlResponse); 
#endif
