#pragma once

#include "vector.h"

namespace gQuake
{

template<class T>
struct Vector<2, T>
{

    union {
        T data[2];
        struct {T x, y;};
    };

    Vector<2, T>();
    Vector<2, T>(T x, T y);
    
    template <int ov_n>
    Vector<2, T>(Vector<ov_n, T> ov);

    inline Vector<2, T> operator+(Vector<2, T>& other) const;
    inline Vector<2, T> operator+=(Vector<2, T>& other);

};

typedef Vector<2, float> vec2f;

/* ===== VECTOR2.INL =====
I was supposed to  make a seperate .inl but clangd hates me so I will just put the
defenitions here.
*/

}

