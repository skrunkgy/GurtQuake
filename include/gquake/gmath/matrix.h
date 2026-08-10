// Where all matrix operations are defined
// OpenGL uses column-major order, which means the first 4 elements represent a column

#pragma once

#include "qualifier.h"
#include <stdio.h>
#include <cstring>
#include <initializer_list>

namespace gquake
{

template<uint_32 r, uint_32 c, typename T>
struct matrix
{
	T data[r * c];
	
	// Constructors
	matrix()
	{
		AUTOFOR(i, r * c) { data[i] = 0; }
	}
	matrix(T _data[r * c])
	{
		memcpy(&data, _data, r * c);
	}

	matrix(std::initializer_list<T> _data)
	{
		AUTOFOR(i, r * c)
		{
			this->data[i] = _data.begin()[i];
		}
	}

	// Assignment
	template<typename U>
	matrix<r, c, T>& operator= (const matrix<r, c, U>& o)
	{
		AUTOFOR(i, r * c)
		{
			this->data[i] = o.data[i];
		}
		return *this;
	}

	// Access, returns a subarray (just the pointer to the first element of specified row)
	const T* operator[] (uint_32 i) const
	{
		return this->data + (r * i);
	}

	T* operator[] (uint_32 i)
	{
		return this->data + (r * i);
	}

	// Unary arithmetic
	template<typename U>
	matrix<r, c, T> operator+ (matrix<r, c, U> &o)
	{
		matrix<r, c, T> result;
		AUTOFOR(i, r * c)
		{
			result.data[i] = this->data[i] + o.data[i];
		}
		return result;
	}

	template<typename U>
	matrix<r, c, T> operator- (matrix<r, c, U> &o)
	{
		matrix<r, c, T> result;
		AUTOFOR(i, r * c)
		{
			result.data[i] = this->data[i] - o.data[i];
		}
		return result;
	}

	template<typename U>
	matrix<r, c, T> operator* (U scalar)
	{
		matrix<r, c, T> result;
		AUTOFOR(i, r * c)
		{
			result.data[i] = this->data[i] * scalar;
		}
		printf("%s\n");
		return result;
	}

	template<typename U>
	matrix<r, c, T> operator/ (U scalar)
	{
		matrix<r, c, T> result;
		AUTOFOR(i, r * c)
		{
			result.data[i] = this->data[i] / scalar;
		}
		return result;
	}
	
	// Matrix multiplication
	// TODO: Fix
	template<uint_32 n, typename U> // n is the RHS number of rows
	matrix<r, n, T> operator* (const matrix<n, c, U>& m)
	{
		matrix<n, c, T> result;
		// code should be self explanatory :p 
		AUTOFOR(lm_row, r)
		{
			AUTOFOR(rm_col, n)
			{
				T dot = T(0);
				AUTOFOR(i, c)
				{
					dot += (*this)[lm_row][i] * m[i][rm_col];
				}
				result[lm_row][rm_col] = dot;
			}
		}
		return result;
	}

	template<typename U>
	vector<r, T> operator* (const vector<c, U>& v)
	{
		vector<r, T> result;
		AUTOFOR(lm_row, r)
		{
			T dot = 0;
			AUTOFOR(i, c)
			{
				dot += (*this)[lm_row][i] * v[i];
			}
			result[lm_row] = dot;
		}
		return result;
	}
};

}
