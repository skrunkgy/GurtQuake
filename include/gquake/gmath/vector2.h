// vector of size 2 specialization!

#pragma once

#include "qualifier.h"

namespace gquake
{

template<typename T>
struct vector<2, T>
{
	union
	{
		T data[2];
		struct {T x, y; };
		struct {T r, g; };
		struct {T u, v; };
	};
	
	// Constructors
	vector()
	{ 
		this->x = T(0); this->y = T(0);
	}
	template<typename U>
	vector(const vector<2, U> &o)
	{ 
		this->x = o.x; this->y = o.y; 
	}
	vector(T _x, T _y) 
	{ 
		this->x =  _x; this->y =  _y; 
	}

	// Assignment
	template<typename U>
	vector<2, T>& operator= (const vector<2, U> &o)
	{
		this->x = o.x;
		this->y = o.y;
		return *this;
	}
	
	// Unary arithmetic operators
	template <typename U>
	vector<2, T> operator+ (const vector<2, U> &o)
	{
		return vector<2, T>(x + o.x, y + o.y);
	}

	template <typename U>
	vector<2, T> operator- (const vector<2, U> &o)
	{
		return vector<2, T>(this->x - o.x, this->y - o.y);
	}
	
	template <typename U>
	vector<2, T> operator* (U scalar)
	{
		return vector<2, T>(this->x * scalar, this->y * scalar);
	}

	template <typename U>
	vector<2, T> operator/ (U scalar)
	{
		return vector<2, T>(this->x / scalar, this->y / scalar);
	}

	template <typename U>
	vector<2, T>& operator+= (const vector<2, U> &o)
	{
		this->x += o.x;
		this->y += o.y;
		return *this;
	}

	template <typename U>
	vector<2, T>& operator-= (const vector<2, U> &o)
	{
		this->x -= o.x;
		this->y -= o.y;
		return *this;
	}

	template <typename U>
	vector<2, T>& operator*= (U scalar)
	{
		this->x *= scalar;
		this->y *= scalar;
		return *this;
	}

	template <typename U>
	vector<2, T>& operator/= (U scalar)
	{
		this->x /= scalar;
		this->y /= scalar;
		return *this;
	}

	// Matrix multiplication (left to right)
	template<uint_32 r, typename U>
	matrix<1, r, T> operator* (const matrix<2, r, U>& o)
	{
		matrix<1, r, T> new_mat;
		AUTOFOR(i, r)
		{
			new_mat[i] = this->x * o[i][0] + this->y * o[i][1];
		}
		return new_mat;
	}

	// Comparisons
	// Will not use greater or lesser, since these are multi component
	template <typename U>
	bool operator== (const vector<2, U> &o)
	{
		return this->x == o.x && this->y == o.y;
	}

	template <typename U>
	bool operator!= (const vector<2, U> &o)
	{
		return this->x != o.x || this->y != o.y;
	}

	// Access modifier
	template<typename length_type>
	T& operator[] (length_type i)
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
	const T& operator[] (length_type i)
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

// Binary operators

template<typename T, typename U>
vector<2, T> operator* (U scalar, const vector<2, T>& v)
{
	return vector<2, T>(v.x * scalar, v.y * scalar);
}

template<typename T, typename U>
vector<2, T> operator/ (U scalar, const vector<2, T>& v)
{
	return vector<2, T>(v.x / scalar, v.y / scalar);
}

}
