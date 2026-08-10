// Provides some math functions

#pragma once

#include "qualifier.h"
#include "../gtypes.h"
#include "../gmath.h"
#include <cmath>

#define GQ_VEC_TEMP template<uint_32 n, typename T> // may incorporate this in other headers... but just makes it easier on the eyes

namespace gquake
{

template<uint_32 n, typename T, typename U>
T dot(vector<n, T> a, vector<n, U> b)
{
	T sum = 0;
	for (int i = 0; i < n; i++)
	{
		sum += a[i] * b[i];
	}
	return std::sqrt(sum); // pesky std math library... rumble fumble...
}

template<typename T, typename U>
vector<3, T> cross(vector<3, T> a, vector<3, U> b)
{
	return vector<3, T>( a.y * b.z - a.z * b.y , a.z * b.x - a.x * b.z , a.x * b.y - a.y * b.x );
}

template<uint_32 n, typename T>
T length(const vector<n, T> &v)
{
	T sum = 0.0f;
	for (int i = 0; i < n; i++)
	{
		sum += v[i] * v[i];
	}
	return std::sqrt(sum);
}

template<uint_32 n, typename T>
vector<n, T> normalized(vector<n, T> &v)
{
	return v / length(v);
}

template<typename T, typename U>
T array_dot(T* a, T* b, uint_32 n)
{
	T result = 0;
	AUTOFOR(i, n)
	{
		result += a[i] * b[i];
	}
	return result;
}

inline vec3 rotate_point(vec3 point, vec3 axis, float_32 angle)
{
	float_32 s = std::sin(angle);
	float_32 c = std::cos(angle);

	mat3x3 rotation_matrix = 
		{
			std::pow(axis.x, 2.0f) * (1.0f - c) + c, axis.x * axis.y * (1.0f - c) - axis.z * s, axis.x * axis.z * (1.0f - c) + axis.y * s,
			axis.x * axis.y * (1.0f - c) + axis.z * s, std::pow(axis.y, 2.0f) * (1.0f - c) + c, axis.y * axis.z * (1.0f - c) - axis.x * s,
			axis.x * axis.z * (1.0f - c) - axis.y * s, axis.y * axis.z * (1.0f - c) + axis.x * s, std::pow(axis.z, 2.0f) * (1.0f - c) + c
		};
	return point * rotation_matrix;
}

}
