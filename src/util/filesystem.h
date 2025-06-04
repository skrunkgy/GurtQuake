#ifndef GQ_FILESYSTEM_H
#define GQ_FILESYSTEM_H

#include <stdio.h>

// Does basic file operations, but will expand this when we have a more complex filesystem
FILE* load_file(char* path);
void store_file(void* fileptr, char* path);

#endif