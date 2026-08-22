// vector3.h || Vector of size 3 implementation


#pragma once

#include <string.h>
#include <cassert>

#include "qualifier.h"

namespace gquake
{

template<typename T>
struct alignas(T) Vector<3, T>
{
	union
	{
		T data[3];
		struct {T x, y, z; };
		struct {T r, g, b; };
		struct {T s, t, u; };
	};
	
	// Constructors
	Vector()
	{ 
		this->x = T(0); this->y = T(0); this->z = T(0);
	}

	template<typename U>
	Vector(const Vector<3, U> &o)
	{ 
		this->x = o.x; this->y = o.y; this->z = o.z; 
	}

	template<uint32_t m, typename U>
	Vector(const Vector<m, U>& o)
	{
		AUTOFOR(i, 3)
		{
			if (i >= m) this->data[i] = T(0);
			else this->data[i] = o.data[i];
		}
	}

	Vector(T _x, T _y, T _z) 
	{ 
		this->x = _x; this->y = _y; this->z = _z; 
	}
	Vector(T* _array)
	{
		memcpy(this->data, _array, 3);
	}

	// Assignment
	template<typename U>
	Vector<3, T>& operator= (const Vector<3, U> &o)
	{
		this->x = o.x;
		this->y = o.y;
		this->z = o.z;
		return *this;
	}

	// Null arithmetic operators
	Vector<3, T> operator- ()
	{
		return (*this) * -1;
	}

	// Unary arithmetic operators
	template <typename U>
	Vector<3, T> operator+ (const Vector<3, U> &o)
	{
		return Vector<3, T>(x + o.x, y + o.y, z + o.z);
	}

	template <typename U>
	Vector<3, T> operator- (const Vector<3, U> &o)
	{
		return Vector<3, T>(this->x - o.x, this->y - o.y, this->z - o.z);
	}
	
	template <typename U>
	Vector<3, T> operator* (U scalar)
	{
		return Vector<3, T>(this->x * scalar, this->y * scalar, this->z * scalar);
	}
	
	template<uint32_t c, typename U>
	Vector<c, T> operator* (const Matrix<3, c, U>& m)
	{
		Vector<c, T> result;
		AUTOFOR(rm_col, c)
		{
			T dot = 0;
			AUTOFOR(i, 3)
			{
				dot += m[i][rm_col] * (*this)[i];
			}
			result[rm_col] = dot;
		}
		return result;
	}

	template <typename U>
	Vector<3, T> operator/ (U scalar)
	{
		return Vector<3, T>(this->x / scalar, this->y / scalar, this->z / scalar);
	}

	template <typename U>
	Vector<3, T>& operator+= (const Vector<3, U> &o)
	{
		this->x += o.x;
		this->y += o.y;
		this->z += o.z;
		return *this;
	}

	template <typename U>
	Vector<3, T>& operator-= (const Vector<3, U> &o)
	{
		this->x -= o.x;
		this->y -= o.y;
		this->z -= o.z;
		return *this;
	}

	template <typename U>
	Vector<3, T>& operator*= (U scalar)
	{
		this->x *= scalar;
		this->y *= scalar;
		this->z *= scalar;
		return *this;
	}

	template <typename U>
	Vector<3, T>& operator/= (U scalar)
	{
		this->x /= scalar;
		this->y /= scalar;
		this->z /= scalar;
		return *this;
	}

	// Comparisons
	// Will not use greater or lesser, since these are multi component
	template <typename U>
	bool operator== (const Vector<3, U> &o)
	{
		return this->x == o.x && this->y == o.y && this->z == o.z;
	}

	template <typename U>
	bool operator!= (const Vector<3, U> &o)
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
Vector<3, T> operator* (U scalar, const Vector<3, T>& v)
{
	return Vector<3, T>(v.x * scalar, v.y * scalar, v.z * scalar);
}

template<typename T, typename U>
Vector<3, T> operator/ (U scalar, const Vector<3, T>& v)
{
	return Vector<3, T>(v.x / scalar, v.y / scalar, v.z / scalar);
}

} // namespace gquake
