// Provides some math functions

#pragma once

#include "../core/gqtypes.h"
#include "math_types.h"
#include "matrix.h"
#include "vector2.h"
#include "vector3.h"
#include "vector4.h"
#include <cmath>

#define GQ_VEC_TEMP template<uint32_t n, typename T> // may incorporate this in other headers... but just makes it easier on the eyes

namespace gquake
{

template<uint32_t n, typename T, typename U>
T dot(Vector<n, T> a, Vector<n, U> b)
{
	T sum = 0;
	for (int i = 0; i < n; i++)
	{
		sum += a[i] * b[i];
	}
	return std::sqrt(sum); // pesky std math library... rumble fumble...
}

template<typename T, typename U>
Vector<3, T> cross(Vector<3, T> a, Vector<3, U> b)
{
	return Vector<3, T>( a.y * b.z - a.z * b.y , a.z * b.x - a.x * b.z , a.x * b.y - a.y * b.x );
}

template<uint32_t n, typename T>
T length(const Vector<n, T> &v)
{
	T sum = 0.0f;
	for (int i = 0; i < n; i++)
	{
		sum += v[i] * v[i];
	}
	return std::sqrt(sum);
}

template<uint32_t n, typename T>
Vector<n, T> normalized(Vector<n, T> &v)
{
	return v / length(v);
}

template<typename T, typename U>
T array_dot(T* a, U* b, uint32_t n)
{
	T result = 0;
	AUTOFOR(i, n)
	{
		result += a[i] * b[i];
	}
	return result;
}

template<typename T>
inline Vector<3, T> rotate_point(Vector<3, T>  point, Vector<3, T> axis, float32_t angle)
{
	float32_t s = std::sin(angle);
	float32_t c = std::cos(angle);

	mat3x3 rotation_matrix = 
		{
			std::pow(axis.x, 2.0f) * (1.0f - c) + c, axis.x * axis.y * (1.0f - c) - axis.z * s, axis.x * axis.z * (1.0f - c) + axis.y * s,
			axis.x * axis.y * (1.0f - c) + axis.z * s, std::pow(axis.y, 2.0f) * (1.0f - c) + c, axis.y * axis.z * (1.0f - c) - axis.x * s,
			axis.x * axis.z * (1.0f - c) - axis.y * s, axis.y * axis.z * (1.0f - c) + axis.x * s, std::pow(axis.z, 2.0f) * (1.0f - c) + c
		};
	return point * rotation_matrix;
}

}
