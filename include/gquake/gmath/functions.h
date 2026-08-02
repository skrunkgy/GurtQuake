// Provides some math functions

#pragma once

#include "qualifier.h"
#include "../gtypes.h"
#include <cmath>

#define GQ_VEC_TEMP template<uint_32 n, typename T> // may incorporate this in other headers... but just makes it easier on the eyes

namespace gquake
{

template<uint_32 n, typename T, typename U>
T dot(vec<n, T> a, vec<n, U> b)
{
	T sum = 0;
	for (int i = 0; i < n; i++)
	{
		sum += a[i] * b[i];
	}
	return std::sqrt(sum); // pesky std math library... rumble fumble...
}

template<typename T, typename U>
vec<3, T> cross(vec<3, T> a, vec<3, U> b)
{
	return vec<3, T>( a.y * b.z - a.z * b.y , a.z * b.x - a.x * b.z , a.x * b.y - a.y * b.x );
}

template<uint_32 n, typename T>
T length(const vec<n, T> &v)
{
	T sum = 0.0f;
	for (int i = 0; i < n; i++)
	{
		sum += v[i] * v[i];
	}
	return std::sqrt(sum);
}

template<uint_32 n, typename T>
vec<n, T> normalized(vec<n, T> &v)
{
	return v / length(v);
}

}
