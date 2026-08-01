// Vector of size 2 specialization!

#pragma once

#include "qualifier.h"

namespace gquake
{

template<typename T>
struct vec<2, T>
{
	union
	{
		struct {T x, y;};
		struct {T r, g;};
		struct {T u, v;};
	};
	
	// Constructors
	vec()
	{ 
		this->x = T(0); this->y = T(0);
	}
	template<typename U>
	vec(const vec<2, U> &o)
	{ 
		this->x = o.x; this->y = o.y; 
	}
	vec(T _x, T _y) 
	{ 
		this->x =  _x; this->y =  _y; 
	}

	// Assignment
	template<typename U>
	vec<2, T>& operator=(const vec<2, U> &o)
	{
		this->x = o.x;
		this->y = o.y;
		return *this;
	}
	
	// binary operators
	template <typename U>
	vec<2, T> operator+ (const vec<2, U> &o)
	{
		return vec<2, T>(x + o.x, y + o.y);
	}

	template <typename U>
	vec<2, T> operator- (const vec<2, U> &o)
	{
		return vec<2, T>(this->x - o.x, this->y - o.y);
	}
	
	template <typename U>
	vec<2, T> operator* (U scalar)
	{
		return vec<2, T>(this->x * scalar, this->y * scalar);
	}

	template <typename U>
	vec<2, T> operator/ (U scalar)
	{
		return vec<2, T>(this->x / scalar, this->y / scalar);
	}

	// Unary operators
	template <typename U>
	vec<2, T>& operator+= (const vec<2, U> &o)
	{
		this->x += o.x;
		this->y += o.y;
		return *this;
	}

	template <typename U>
	vec<2, T>& operator-= (const vec<2, U> &o)
	{
		this->x -= o.x;
		this->y -= o.y;
		return *this;
	}

	template <typename U>
	vec<2, T>& operator*= (U scalar)
	{
		this->x *= scalar;
		this->y *= scalar;
		return *this;
	}

	template <typename U>
	vec<2, T>& operator/= (U scalar)
	{
		this->x /= scalar;
		this->y /= scalar;
		return *this;
	}

	// Comparisons
	// Will not use greater or lesser, since these are multi component
	template <typename U>
	bool operator== (const vec<2, U> &o)
	{
		return this->x == o.x && this->y == o.y;
	}

	template <typename U>
	bool operator!= (const vec<2, U> &o)
	{
		return this->x != o.x || this->y != o.y;
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
			default:;
		}
	}
};

}
