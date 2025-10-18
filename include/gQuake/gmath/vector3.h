// vector3.h - header for the Vector3 class (UNFINISHED, UNIMPLEMENTED)

#pragma once

#include "../gtypes.h"

namespace gQuake
{

template<class T>
struct Vector3
{

    // Data

    union {
        T data[3];
        struct {T x, y, z;};
        struct {T r, g, b;};
    };
};

typedef Vector3<float32> vec3f;

}