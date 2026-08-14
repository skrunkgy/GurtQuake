// vectortor of size 4 specialization!

#pragma once

#include <string.h>
#include <cassert>

#include "qualifier.h"

namespace gquake
{

template<typename T>
struct alignas(T) vector<4, T>
{
	union
	{
		T data[4];
		struct {T x, y, z, w; };
		struct {T r, g, b, a; };
		struct {T u, v, s, t; };
	};
	
	// Constructors
	vector()
	{ 
		this->x = T(0); this->y = T(0); this->z = T(0); this->w = T(0);
	}
	template<typename U>
	vector(const vector<4, U> &o)
	{ 
		this->x = o.x; this->y = o.y; this->z = o.z; this->w = o.w;
	}
	vector(T _x, T _y, T _z, T _w) 
	{ 
		this->x = _x; this->y = _y; this->z = _z; this->w = _w;
	}
	vector(T* _array)
	{
		memcpy(this->data, _array, 4);
	}

	// Assignment
	template<typename U>
	vector<4, T>& operator= (const vector<4, U> &o)
	{
		this->x = o.x;
		this->y = o.y;
		this->z = o.z;
		this->w = o.w;
		return *this;
	}

	// Null arithmetic operators
	vector<4, T> operator- ()
	{
		return (*this) * -1;
	}

	// Unary arithmetic operators
	template <typename U>
	vector<4, T> operator+ (const vector<4, U> &o)
	{
		return vector<4, T>(this->x + o.x, this->y + o.y, this->z + o.z, this->w + o.w);
	}

	template <typename U>
	vector<4, T> operator- (const vector<4, U> &o)
	{
		return vector<4, T>(this->x - o.x, this->y - o.y, this->z - o.z, this->w - o.w);
	}
	
	template <typename U>
	vector<4, T> operator* (U scalar)
	{
		return vector<4, T>(this->x * scalar, this->y * scalar, this->z * scalar, this->w * scalar);
	}

	template <typename U>
	vector<4, T> operator/ (U scalar)
	{
		return vector<4, T>(this->x / scalar, this->y / scalar, this->z / scalar, this->w / scalar);
	}

	template <typename U>
	vector<4, T>& operator+= (const vector<4, U> &o)
	{
		this->x += o.x;
		this->y += o.y;
		this->z += o.z;
		this->w += o.w;
		return *this;
	}

	template <typename U>
	vector<4, T>& operator-= (const vector<4, U> &o)
	{
		this->x -= o.x;
		this->y -= o.y;
		this->z -= o.z;
		this->w -= o.w;
		return *this;
	}

	template <typename U>
	vector<4, T>& operator*= (U scalar)
	{
		this->x *= scalar;
		this->y *= scalar;
		this->z *= scalar;
		this->w *= scalar;
		return *this;
	}

	template <typename U>
	vector<4, T>& operator/= (U scalar)
	{
		this->x /= scalar;
		this->y /= scalar;
		this->z /= scalar;
		this->w /= scalar;
		return *this;
	}

	// Comparisons
	// Will not use greater or lesser, since these are multi component
	template <typename U>
	bool operator== (const vector<4, U> &o)
	{
		return this->x == o.x && this->y == o.y && this->z == o.z && this->w == o.w;
	}

	template <typename U>
	bool operator!= (const vector<4, U> &o)
	{
		return this->x != o.x || this->y != o.y || this->z != o.z || this->w != o.w;
	}

	// Access modifier
	template<typename int_type>
	T& operator[] (int_type i)
	{
		assert (i < 4);
		switch(i)
		{	
			default:
			case 0:
				return this->x; break;
			case 1:
				return this->y; break;
			case 2:
				return this->z; break;
			case 3:
				return this->w; break;
		}
	}

	template<typename int_type>
	const T& operator[] (int_type i) const
	{
		assert (i < 4);
		switch(i)
		{	
			default:
			case 0:
				return this->x; break;
			case 1:
				return this->y; break;
			case 2:
				return this->z; break;
			case 3:
				return this->w; break;
		}
	}
};

// Binary operators

template<typename T, typename U>
vector<4, T> operator* (U scalar, const vector<4, T>& v)
{
	return vector<4, T>(v.x * scalar, v.y * scalar, v.w * scalar, v.w * scalar);
}

template<typename T, typename U>
vector<4, T> operator/ (U scalar, const vector<4, T>& v)
{
	return vector<4, T>(v.x / scalar, v.y / scalar, v.z / scalar, v.w / scalar);
}

}
