#pragma once

#include "../gtypes.h"
#include "../gmath.h"

namespace gQuake
{

class Camera : public gqObject
{

public:
    Camera();
    Camera(vec3f position, vec3f rotation, vec3f up, float fov, float aspratio, float near, float far);
    

};
    
}