// Where all matrix operations are defined
// OpenGL uses column-major order, which means the first 4 elements represent a column

#pragma once

#include "qualifier.h"
#include <stdio.h>
#include <cstring>
#include <initializer_list>

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

	matrix(std::initializer_list<T> _data)
	{
		AUTOFOR(i, c * r)
		{
			this->data[i] = _data.begin()[i];
		}
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

	// Access, returns a subarray (just the pointer to the first element of specified row)
	const T* operator[] (uint_32 i) const
	{
		return this->data + (c * i);
	}

	T* operator[] (uint_32 i)
	{
		return this->data + (c * i);
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

	template<typename U>
	matrix<c, r, T> operator- (matrix<c, r, U> &o)
	{
		matrix<c, r, T> result;
		AUTOFOR(i, c * r)
		{
			result.data[i] = this->data[i] - o.data[i];
		}
		return result;
	}

	template<typename U>
	matrix<c, r, T> operator* (U scalar)
	{
		matrix<c, r, T> result;
		AUTOFOR(i, c * r)
		{
			result.data[i] = this->data[i] * scalar;
		}
		printf("%s\n");
		return result;
	}

	template<typename U>
	matrix<c, r, T> operator/ (U scalar)
	{
		matrix<c, r, T> result;
		AUTOFOR(i, c * r)
		{
			result.data[i] = this->data[i] / scalar;
		}
		return result;
	}
	
	// Matrix multiplication
	template<uint_32 n> // n is the RHS number of rows
	matrix<c, n, T> operator* (const matrix<r, n, T>& b)
	{
		matrix<c, n, T> result;
		// code should be self explanatory :p 
		AUTOFOR(lm_col, c)
		{
			AUTOFOR(rm_row, n)
			{
				T dot = T(0);
				AUTOFOR(i, r)
				{
					dot += (*this)[lm_col][i] * b[i][rm_row];
				}
				result[lm_col][rm_row] = dot;
			}
		}
		return result;
	}

};

}
