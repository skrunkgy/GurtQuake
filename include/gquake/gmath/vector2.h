// vector of size 2 specialization!

#pragma once

#include "qualifier.h"
#include <cassert>

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

	// Multiplication with matrices
	template<uint_32 m, typename U> // n is the RHS number of columns
	vector<m, T> operator* (matrix<2, m, U> mat)
	{
		vector<m, T> result;
		// code should be self explanatory :p 
		AUTOFOR(rm_row, m)
		{
			T dot = T(0);
			AUTOFOR(i, 2)
			{
				dot += (*this)[i] * mat[i][rm_row];
			}
			result[rm_row] = dot;
		}
		return result;
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
