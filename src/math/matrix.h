// matrix.h || Generic struct for matrices, uses row-major order 

#pragma once

#include <cassert>
#include <stdio.h>
#include <string.h>
#include <initializer_list>

#include "qualifier.h"
#include "../core/gqtypes.h"

namespace gquake
{

template<uint32_t r, uint32_t c, typename T>
struct alignas(T) Matrix
{
	Vector<c, T> data[r];
	
	// Constructors
	Matrix()
	{
		if (r == c)
		{
			AUTOFOR(i, r) this->data[i][i] = T(1);
		}
	}
	Matrix(T _data[r * c])
	{
		// Under the assumption it is tightly packed
		memcpy(&data, _data, r * c);
	}

	Matrix(std::initializer_list<T> _data)
	{
		assert (_data.size() == r * c);
		AUTOFOR(i, r) AUTOFOR(j, c)
		{
			this->data[i][j] = _data.begin()[i * c + j];
		}
	}

	template <uint32_t _r, uint32_t _c, typename U>
	Matrix(const Matrix<_r, _c, U>& o)
	{
		AUTOFOR(i, r)
		{
			if (i >= _r) this->data[i] = Vector<c, T>();
			else this->data[i] = o.data[i];
			AUTOFOR(j, c)
			{
				if ((i >= _r || j >= _c) && r == c && i == j)
				{
					this->data[i][j] = T(1);
				}
			}
		}
	}

	// Assignment
	template <typename U>
	Matrix<r, c, T>& operator= (const Matrix<r, c, U>& o)
	{
		AUTOFOR(i, r)
		{
			this->data[i] = o.data[i];
		}
		return *this;
	}

	// Access, returns a subarray (just the pointer to the first element of specified row)
	const Vector<c, T>& operator[] (uint32_t i) const
	{
		return this->data[i];
	}

	Vector<c, T>& operator[] (uint32_t i)
	{
		return this->data[i];
	}

	// Unary arithmetic
	template<typename U>
	Matrix<r, c, T> operator+ (Matrix<r, c, U> &o)
	{
		Matrix<r, c, T> result;
		AUTOFOR(i, r)
		{
			result.data[i] = this->data[i] + o.data[i];
		}
		return result;
	}

	template<typename U>
	Matrix<r, c, T> operator- (Matrix<r, c, U> &o)
	{
		Matrix<r, c, T> result;
		AUTOFOR(i, r)
		{
			result.data[i] = this->data[i] - o.data[i];
		}
		return result;
	}

	template<typename U>
	Matrix<r, c, T> operator* (U scalar)
	{
		Matrix<r, c, T> result;
		AUTOFOR(i, r)
		{
			result.data[i] = this->data[i] * scalar;
		}
		return result;
	}

	template<typename U>
	Matrix<r, c, T> operator/ (U scalar)
	{
		Matrix<r, c, T> result;
		AUTOFOR(i, r)
		{
			result.data[i] = this->data[i] / scalar;
		}
		return result;
	}
	
	// Matrix multiplication
	template<uint32_t n, typename U> // n is the RHS number of rows
	Matrix<r, n, T> operator* (const Matrix<n, c, U>& m)
	{
		Matrix<n, c, T> result;
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
	
	// We are assuming our vector is a column
	template<typename U>
	Vector<r, T> operator* (const Vector<c, U>& v)
	{
		Vector<r, T> result;
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

} // namespace gquake
