#ifndef SERVERFUNCTIONS_H
#define SERVERFUNCTIONS_H

#include "httpfunctions.h"

int initialize_server(void);
int file_length(char *path);
char *pull_html(const char* path, char *html, int htmlLength); 
#endif
