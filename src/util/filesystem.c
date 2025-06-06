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
    char* returnBuffer = malloc(128);
    returnBuffer[0] = '\0';

    char buffer[128]; // Get rid of magic number
    
    while (fgets(buffer, 128, fptr))
    {
        returnBuffer = realloc(returnBuffer, sizeof(buffer));
        strcat(returnBuffer, buffer);
    }
    return returnBuffer;
}