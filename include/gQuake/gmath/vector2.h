#pragma once

#include "../gtypes.h"
#include "../gmath.h"

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

    inline T            operator[](uint_32& n) const;

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

/*
========================= VECTOR2.INL =========================
I was supposed to  make a seperate .inl but clangd hates me so
I will just put the defenitions here.
*/

namespace gQuake {

template <typename T>
Vector2<T>::Vector2():
    x(0), y(0) {}

template <typename T>
Vector2<T>::Vector2(T s):
    x(s), y(s) {}

template <typename T>
Vector2<T>::Vector2(T _x, T _y):
    x(_x), y(_y) {}


template <typename T>
inline Vector2<T> Vector2<T>::operator+(const Vector2<T>& other) const
{
    return Vector2(x + other.x, y + other.y);
}

template <typename T>
inline void Vector2<T>::operator+=(const Vector2<T>& other)
{
    x += other.x;
    y += other.y;
}

template <typename T>
inline Vector2<T> Vector2<T>::operator*(const T& scalar) const
{
    return Vector2<T>(x * scalar, y * scalar);
}
// We need to write a non-member overloader when we have a S * V.
template <typename T, typename C>
inline Vector2<T> operator*(const C& scalar, const Vector2<T>& vec)
{
    return Vector2<T>(vec.x * scalar, vec.y * scalar);
}

} // namespace gQuake