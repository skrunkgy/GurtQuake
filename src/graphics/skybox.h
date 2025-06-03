#ifndef GQ_SKYBOX_H
#define GQ_SKYBOX_H

#include <GL/glew.h>

// Max skybox resolution (width)
// TODO: MAKE PROJECT OPTIONS
#define GQ_SKYBOX_MAX 1024

typedef struct
{
    char* filename;
    GLuint textureID;
    GLuint shaderID; // we might not need this, since we will compile a skybox shader with only an argument

} gq_Skybox;

// Set up the skybox. The extension will be .gsb. Will make a tool for making skyboxes.
void gq_SetSkybox(gq_Skybox* sb, char* filename);
void gq_DrawSkybox(gq_Skybox* sb);

#endif