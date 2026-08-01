// Provides some math functions

#include "qualifier.h"
#include "../gtypes.h"

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
	return sum;
}

template<typename T, typename U>
vec<3, T> cross(vec<3, T> a, vec<3, U> b)
{
	return vec<3, T>( a.y * b.z - a.z * b.y , a.z * b.x - a.x * b.z , a.x * b.y - a.y * b.x );
}

}
