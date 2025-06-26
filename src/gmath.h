
/* ======================================  GMATH ======================================
This is a header library for gQuake's math functions. Anything related to linear
algebra or whatever will be stored in here. It will also 
*/

#include <stdexcept>

namespace gQuake
{

// TO DO: PARAMETERIZE IT
template <int n, class T>
struct Vector
{
	T data[n];

	inline T operator[](int index)
	{
		if (index >= n) throw std::runtime_error("Invalid access\n");
		return data[index];
	}
	inline Vector<n, T> operator+(Vector<n, T> other)
	{
		for (int i = 0; i < n; i++) this->data[i] += other.data[i];
		return *this;
	}
	inline Vector<n, T> operator-(Vector<n, T> other)
	{
		for (int i = 0; i < n; i++) this->data[i] -= other[i];
		return *this;
	}

	template <class ST> // scalar type
	inline Vector<n, T> operator*(ST scalar)
	{
		for (int i = 0; i < n; i++) this->data[i] * scalar;
		return *this;
	}

};

template <int n, class T>
T dot(Vector<n, T> a, Vector<n, T> b) // dot product: MOVE OUT OF THE STRUCT AND USE FREE FUNCTIONS
{
	T total = 0;
	for (int i = 0; i < n; i++) total += a[i] * b[i];
	return total;
}

template<>
struct Vector<2, float>
{
	union
	{
		float data[2];
		struct {float x, y;};
	};
	inline float operator[](int index)
	{
		if (index >= 2) throw std::runtime_error("Invalid access\n");
		return data[index];
	}
	inline Vector<2, float> operator+(Vector<2, float> other)
	{
		for (int i = 0; i < 2; i++) this->data[i] += other.data[i];
		return *this;
	}
	inline Vector<2, float> operator-(Vector<2, float> other)
	{
		for (int i = 0; i < 2; i++) this->data[i] -= other[i];
		return *this;
	}

	template <class ST> // scalar type
	inline Vector<2, float> operator*(ST scalar)
	{
		for (int i = 0; i < 2; i++) this->data[i] * scalar;
		return *this;
	}
};

template<>
struct Vector<3, float>
{
	union
	{
		float data[3];
		struct {float x, y, z;};
		struct {float r, g, b;};
	};
};

template<>
struct Vector<4, float>
{
	union
	{
		float data[4];
		struct {float x, y, z, w;};
		struct {float r, g, b, a;};
	};
};

typedef Vector<2, float> vec2;
typedef Vector<3, float> vec3;
typedef Vector<4, float> vec4;

// Major column order to comply with OpenGL
// Generic matrix template, might just use mat3 and mat4 since we don't really need much. consider these!
template <int rows, int columns>
struct mat
{
	float data[rows][columns]; // main array, then sub array
};

}