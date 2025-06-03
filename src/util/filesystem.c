#include <util/filesystem.h>
#include <stdlib.h>
#include <stdio.h>

// ok i know this looks retarded but in the future i will implement a file system
FILE* load_file(char* path)
{
    FILE *fptr = fopen(path, "r");
}

// does nothing for now
void store_file(void* fileptr, char* path)
{
    return;
};