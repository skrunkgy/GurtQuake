#include <stdio.h>
#include <string.h>
#include <util/filesystem.h>

int main()
{
    FILE *fptr = fopen("resources/shaders/null.vs", "r");

    const char* src = get_file_buffer(fptr);

    printf("%s", src);
}