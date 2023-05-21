#ifndef SERVERFUNCTIONS_H
#define SERVERFUNCTIONS_H
#include <stdbool.h>

#include "httpfunctions.h"

int initialize_server(void);
size_t file_length(char *path);
unsigned char *pull_file(char* path, unsigned char *file, size_t fileLength); 
#endif
