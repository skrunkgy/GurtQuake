/*
======================= MATRIX.H =======================
Here is where the generic matrix will be stored. I won't
make tempalate specializations but I will make some
typedefs.

*/

#pragma once

#include "gmath.h"

namespace gQuake
{

template <int rows, int columns, class T>
struct Matrix
{

    T data[rows * columns];

    // Constructors

    

    // Special constructors

    Matrix<1, 2, T>(const Vector2<T>& _vec);
    // inline Matrix<1, 3, T>(const Vector3<T>& _vec);
    // inline Matrix<1, 4, T>(const Vector4<T>& _vec);

};

}