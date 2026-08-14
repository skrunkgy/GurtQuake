// vector2.h || Vector of size 2 implementation

#pragma once

#include <string.h>
#include <cassert>

#include "qualifier.h"

namespace gquake
{

template<typename T>
struct alignas(T) Vector<2, T>
{
	union
	{
		T data[2];
		struct {T x, y; };
		struct {T r, g; };
		struct {T u, v; };
	};
	
	// Constructors
	Vector()
	{ 
		this->x = T(0); this->y = T(0);
	}
	template<typename U>
	Vector(const Vector<2, U> &o)
	{ 
		this->x = o.x; this->y = o.y; 
	}
	Vector(T _x, T _y) 
	{ 
		this->x =  _x; this->y =  _y; 
	}
	Vector(T* _array)
	{
		memcpy(this->data, _array, 2);
	}

	// Assignment
	template<typename U>
	Vector<2, T>& operator= (const Vector<2, U> &o)
	{
		this->x = o.x;
		this->y = o.y;
		return *this;
	}

	// Null arithmetic operators
	Vector<2, T> operator-()
	{
		return (*this) * -1;
	}
	
	// Unary arithmetic operators
	template <typename U>
	Vector<2, T> operator+ (const Vector<2, U> &o)
	{
		return Vector<2, T>(x + o.x, y + o.y);
	}

	template <typename U>
	Vector<2, T> operator- (const Vector<2, U> &o)
	{
		return Vector<2, T>(this->x - o.x, this->y - o.y);
	}

	template <typename U>
	Vector<2, T> operator* (U scalar)
	{
		return Vector<2, T>(this->x * scalar, this->y * scalar);
	}

	template <typename U>
	Vector<2, T> operator/ (U scalar)
	{
		return Vector<2, T>(this->x / scalar, this->y / scalar);
	}

	template <typename U>
	Vector<2, T>& operator+= (const Vector<2, U> &o)
	{
		this->x += o.x;
		this->y += o.y;
		return *this;
	}

	template <typename U>
	Vector<2, T>& operator-= (const Vector<2, U> &o)
	{
		this->x -= o.x;
		this->y -= o.y;
		return *this;
	}

	template <typename U>
	Vector<2, T>& operator*= (U scalar)
	{
		this->x *= scalar;
		this->y *= scalar;
		return *this;
	}

	template <typename U>
	Vector<2, T>& operator/= (U scalar)
	{
		this->x /= scalar;
		this->y /= scalar;
		return *this;
	}

	// Comparisons
	// Will not use greater or lesser, since these are multi component
	template <typename U>
	bool operator== (const Vector<2, U> &o)
	{
		return this->x == o.x && this->y == o.y;
	}

	template <typename U>
	bool operator!= (const Vector<2, U> &o)
	{
		return this->x != o.x || this->y != o.y;
	}

	// Access modifier
	template<typename int_type>
	T& operator[] (int_type i)
	{
		assert (i < 2);
		switch(i)
		{	
			default:
			case 0:
				return this->x; break;
			case 1:
				return this->y; break;
		}
	}

	template<typename int_type>
	const T& operator[] (int_type i) const
	{
		assert (i < 2);
		switch(i)
		{
			default:
			case 0:
				return this->x; break;
			case 1:
				return this->y; break;
		}
	}
};

// Binary operators

template<typename T, typename U>
Vector<2, T> operator* (U scalar, const Vector<2, T>& v)
{
	return Vector<2, T>(v.x * scalar, v.y * scalar);
}

template<typename T, typename U>
Vector<2, T> operator/ (U scalar, const Vector<2, T>& v)
{
	return Vector<2, T>(v.x / scalar, v.y / scalar);
}

}
