// Where all matrix operations are defined
// OpenGL uses column-major order, which means the first 4 elements represent a column

#pragma once

#include "qualifier.h"
#include <stdlib.h>

namespace gquake
{

template<uint_32 c, uint_32 r, typename T>
struct matrix
{
	T data[c * r];
	
	// Constructors
	matrix()
	{
		AUTOFOR(i, c * r) { data[i] = 0; }
	}
	matrix(T _data[c * r])
	{
		memcpy(&data, _data, c * r);
	}

	// Assignment
	template<typename U>
	matrix<c, r, T>& operator= (const matrix<c, r, U>& o)
	{
		AUTOFOR(i, c * r)
		{
			this->data[i] = o.data[i];
		}
		return *this;
	}
	
	// Assignment: vector -> matrix
	// template<typename U>
	// matrix<1, r, T>& operator= (const vector<r, U>& o)
	// {
	// 	AUTOFOR(i, r)
	// 	{
	// 		this->data[i] = o.data[i];
	// 	}
	// }

	// Access, returns a subarray (just the pointer to the first element of specified column)
	T* operator[] (uint_32 i)
	{
		return this->data + (r * i);
	}

	// Unary arithmetic
	template<typename U>
	matrix<c, r, T> operator+ (matrix<c, r, U> &o)
	{
		matrix<c, r, T> result;
		AUTOFOR(i, c * r)
		{
			result.data[i] = this->data[i] + o.data[i];
		}
		return result;
	}

};

// Binary arithmetic operators

}
