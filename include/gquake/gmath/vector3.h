#include "qualifier.h"

namespace gquake
{

template<typename T>
struct vec<3, T>
{
	union
	{
		struct {T x, y, z; };
		struct {T r, g, b; };
		struct {T u, v, s; };
	};
	
	// Constructors
	vec()
	{
		this->x = T(0); this->y = T(0); this->z = T(0);
	}
	template<typename U> vec(const vec<3, U> &o)
	{
		this->x = o.x; this->y = o.y; this->z = o.z;
	}
	vec(T _x, T _y, T _z)
	{
		this->x = _x; this->y = _y; this->z = _z;
	}

	// Assignment
	template<typename U>
	vec<3, T>& operator=(const vec<3, U> &o)
	{
		this->x = o.x;
		this->y = o.y;
		this->z = o.z;
		return *this;
	}
	
	// binary operators
	template <typename U>
	vec<3, T> operator+ (const vec<3, U> &o)
	{
		return vec<2, T>(x + o.x, y + o.y, z + o.z);
	}

	template <typename U>
	vec<2, T> operator- (const vec<3, U> &o)
	{
		return vec<2, T>(this->x - o.x, this->y - o.y, this->z - o.z);
	}
	
	template <typename U>
	vec<2, T> operator* (U scalar)
	{
		return vec<2, T>(this->x * scalar, this->y * scalar, this->z * scalar);
	}

	template <typename U>
	vec<2, T> operator/ (U scalar)
	{
		return vec<2, T>(this->x / scalar, this->y / scalar, this->z / scalar);
	}

	// Unary operators
	template <typename U>
	vec<2, T>& operator+= (const vec<2, U> &o)
	{
		this->x += o.x;
		this->y += o.y;
		this->z += o.z;
		return *this;
	}

	template <typename U>
	vec<2, T>& operator-= (const vec<2, U> &o)
	{
		this->x -= o.x;
		this->y -= o.y;
		this->z -= o.z;
		return *this;
	}

	template <typename U>
	vec<2, T>& operator*= (U scalar)
	{
		this->x *= scalar;
		this->y *= scalar;
		this->z *= scalar;
		return *this;
	}

	template <typename U>
	vec<2, T>& operator/= (U scalar)
	{
		this->x /= scalar;
		this->y /= scalar;
		this->z /= scalar;
		return *this;
	}

	// Comparisons
	// Will not use greater or lesser, since these are multi component
	template <typename U>
	bool operator== (const vec<2, U> &o)
	{
		return this->x == o.x && this->y == o.y && this->z == o.z;
	}

	template <typename U>
	bool operator!= (const vec<2, U> &o)
	{
		return this->x != o.x || this->y != o.y || this->z != o.z;
	}

	// Access modifier
	template<typename length_type>
	T& operator[](length_type i)
	{
		switch(i)
		{	
			case 0:
				return this->x; break;
			case 1:
				return this->y; break;
			case 2:
				return this->z; break;
			default:;
		}
	}

	template<typename length_type>
	const T& operator[](length_type i)
	{
		switch(i)
		{	
			case 0:
				return this->x; break;
			case 1:
				return this->y; break;
			case 2:
				return this->z; break;
			default:;
		}
	}
};

}
