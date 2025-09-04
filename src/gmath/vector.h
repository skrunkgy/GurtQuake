/*
===== GURT MATH VECTOR.H =====
This is a generic setup for 
*/

#pragma once

#include <stdexcept>

namespace gQuake
{

template <int n, class T>
struct Vector
{
	T data[n];
};

}