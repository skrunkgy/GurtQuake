// vector2.h - a vector2 class (UNFINISHED, IMPLEMENTED)

#pragma once

#include "../gtypes.h"

namespace gQuake
{

template<typename T>
struct Vector2
{

    // Data

    union {
        T data[2];
        struct {T x, y;};
    };

    // Constructors

    Vector2();
    Vector2(T s);
    Vector2(T x, T y);
    Vector2(T arr[]);

    // Operator overloads

    inline T operator[](uint_32& n) const;

    inline Vector2 operator+(const Vector2& o_vec) const;
    inline void operator+=(const Vector2& o_vec);
    inline Vector2 operator-(const Vector2& o_vec) const;
    inline void operator-=(const Vector2& o_vec);

    inline Vector2 operator*(const T& scalar) const;
    inline void operator*=(const T& scalar);

    // TODO: typecast overloading!
    // TODO: matrix multiplication!

    // House functions

    inline T dot(Vector2& other);

};

typedef Vector2<float32> vec2f;

}