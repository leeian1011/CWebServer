#ifndef SERVERFUNCTIONS_H
#define SERVERFUNCTIONS_H

#include "httpfunctions.h"

int initialize_server(void);
size_t file_length(char *path);
char *pull_html(const char* path, char *html, size_t htmlLength); 
#endif
