#include <util/filesystem.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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

void* get_file_buffer(FILE* fptr)
{
    char* returnBuffer = calloc(1, 1);

    char buffer[512]; // Get rid of magic number
    
    while (fgets(buffer, 512, fptr))
    {
        char* newPTR = realloc(returnBuffer, strlen(returnBuffer) + strlen(buffer) + 2);
        strcat(newPTR, buffer);
        returnBuffer = newPTR;
    }

    return returnBuffer;
}