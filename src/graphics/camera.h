#ifndef GQ_CAMERA_H
#define GQ_CAMERA_H

#include <util/gmath.h>

typedef struct
{
    vec3 position;
    vec3 look;
    float fov;
    float near;
    float far;
    vec3 rotation;

} gq_Camera;

#endif