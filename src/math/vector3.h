// vectortor of size 3 specialization!

#pragma once

#include <string.h>
#include <cassert>

#include "qualifier.h"

namespace gquake
{

template<typename T>
struct alignas(T) vector<3, T>
{
	union
	{
		T data[3];
		struct {T x, y, z; };
		struct {T r, g, b; };
		struct {T u, v, s; };
	};
	
	// Constructors
	vector()
	{ 
		this->x = T(0); this->y = T(0); this->z = T(0);
	}
	template<typename U>
	vector(const vector<3, U> &o)
	{ 
		this->x = o.x; this->y = o.y; this->z = o.z; 
	}
	vector(T _x, T _y, T _z) 
	{ 
		this->x = _x; this->y = _y; this->z = _z; 
	}
	vector(T* _array)
	{
		memcpy(this->data, _array, 3);
	}

	// Assignment
	template<typename U>
	vector<3, T>& operator= (const vector<3, U> &o)
	{
		this->x = o.x;
		this->y = o.y;
		this->z = o.z;
		return *this;
	}

	// Null arithmetic operators
	vector<3, T> operator- ()
	{
		return (*this) * -1;
	}

	// Unary arithmetic operators
	template <typename U>
	vector<3, T> operator+ (const vector<3, U> &o)
	{
		return vector<3, T>(x + o.x, y + o.y, z + o.z);
	}

	template <typename U>
	vector<3, T> operator- (const vector<3, U> &o)
	{
		return vector<3, T>(this->x - o.x, this->y - o.y, this->z - o.z);
	}
	
	template <typename U>
	vector<3, T> operator* (U scalar)
	{
		return vector<3, T>(this->x * scalar, this->y * scalar, this->z * scalar);
	}

	template <typename U>
	vector<3, T> operator/ (U scalar)
	{
		return vector<3, T>(this->x / scalar, this->y / scalar, this->z / scalar);
	}

	template <typename U>
	vector<3, T>& operator+= (const vector<3, U> &o)
	{
		this->x += o.x;
		this->y += o.y;
		this->z += o.z;
		return *this;
	}

	template <typename U>
	vector<3, T>& operator-= (const vector<3, U> &o)
	{
		this->x -= o.x;
		this->y -= o.y;
		this->z -= o.z;
		return *this;
	}

	template <typename U>
	vector<3, T>& operator*= (U scalar)
	{
		this->x *= scalar;
		this->y *= scalar;
		this->z *= scalar;
		return *this;
	}

	template <typename U>
	vector<3, T>& operator/= (U scalar)
	{
		this->x /= scalar;
		this->y /= scalar;
		this->z /= scalar;
		return *this;
	}

	// Comparisons
	// Will not use greater or lesser, since these are multi component
	template <typename U>
	bool operator== (const vector<3, U> &o)
	{
		return this->x == o.x && this->y == o.y && this->z == o.z;
	}

	template <typename U>
	bool operator!= (const vector<3, U> &o)
	{
		return this->x != o.x || this->y != o.y || this->z != o.z;
	}

	// Access modifier
	template<typename int_type>
	T& operator[] (int_type i)
	{
		assert (i < 3);
		switch(i)
		{	
			default:
			case 0:
				return this->x; break;
			case 1:
				return this->y; break;
			case 2:
				return this->z; break;
		}
	}

	template<typename int_type>
	const T& operator[] (int_type i) const
	{
		assert (i < 3);
		switch(i)
		{	
			default:
			case 0:
				return this->x; break;
			case 1:
				return this->y; break;
			case 2:
				return this->z; break;
		}
	}
};

// Binary operators

template<typename T, typename U>
vector<3, T> operator* (U scalar, const vector<3, T>& v)
{
	return vector<3, T>(v.x * scalar, v.y * scalar, v.z * scalar);
}

template<typename T, typename U>
vector<3, T> operator/ (U scalar, const vector<3, T>& v)
{
	return vector<3, T>(v.x / scalar, v.y / scalar, v.z / scalar);
}

}
