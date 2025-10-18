
/*
vector2.inl - inline functions for the Vector2 class
*/

#include "vector2.h"

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