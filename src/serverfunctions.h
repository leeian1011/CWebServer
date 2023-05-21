#ifndef SERVERFUNCTIONS_H
#define SERVERFUNCTIONS_H
#include <stdbool.h>

#include "httpfunctions.h"

int initialize_server(void);
bool is_icon_request(char *requestedUrl);
size_t file_length(char *path);
char *pull_file(char* path, char *file, size_t fileLength); 
#endif
