#include "skybox.h"

#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>

// To load a skybox
// Skyboxes dont need to be stored, they just need to loaded once per map.
void gq_SetSkybox(gq_Skybox* sb, char* filename)
{
    sb->filename = filename;

    FILE *fptr = fopen(filename, "r");
    // TODO: handle NULL if file not found!

    // First 4 bytes will be the width (and height) of the map. Each pixel is 4 bytes, so the file size SHOULD be 4 + (height * height * 4) bytes
    int width;
    fread(&width, 4, 1, fptr);

    // Error handling size
    if (width > GQ_SKYBOX_MAX) // TODO: Make this a project parameter instead!
    {
        printf("Size of skybox too big.\n");
        return;
    }

    char* data = calloc(4, width * width);

    glBindTexture(GL_TEXTURE_CUBE_MAP, sb->textureID);
    for (int i = 0; i < 6; i++)
    {

        fread(data, 4, width * width, fptr);

        glTexImage2D(
            GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
            0, GL_RGBA, width, width, 0,
            GL_RGBA, GL_UNSIGNED_BYTE, 
            data);
        
    }

    free(data);
}

void gq_DrawSkybox(gq_Skybox* sb)
{
    // TODO
    return;
}