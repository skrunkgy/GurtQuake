#ifndef GQ_FILESYSTEM_H
#define GQ_FILESYSTEM_H

#include <stdio.h>

FILE* load_file(char* path);
void store_file(void* fileptr, char* path);

#endif