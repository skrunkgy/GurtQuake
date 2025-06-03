// THIS WILL GENERATE .gsb FILES FROM A FOLDER
// To generate the necessary files, use this tool: https://matheowis.github.io/HDRI-to-CubeMap/

#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char** kwarg)
{
    if (argc != 2)
    {
        char buff;
        printf("Please input 1 argument (drag or drop a file or folder!) Use -h or --help for more info.\nPress enter to exit.\n");
        scanf("%");
        return 0;
    }

    if (strcmp(kwarg[1], "-h") == 0 || strcmp(kwarg[1], "--help") == 0)
    {
        printf("USAGE\n\tgengsb [file/folder]\nYou can also drag and drop a file or folder onto the exe.");
        return 0;
    }

    struct stat checkfile;
    stat(kwarg[1], &checkfile);
    if (S_ISDIR(checkfile.st_mode))
    {
        printf("directory\n");
        // generate a .gsb by importing 6 files each...
    }
    else if (S_ISREG(checkfile.st_mode))
    {
        printf("file\n");
    }
    else
    {
        printf("Invalid file. Exiting...");
    }

    return 0;

}