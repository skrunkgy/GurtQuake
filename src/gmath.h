
/* ======================================  GMATH ======================================
This is a header library for gQuake's math functions. Anything related to linear
algebra or whatever will be stored in here. It will also 
*/

#include <stdexcept>

namespace gQuake
{

// TO DO: PARAMETERIZE IT
template <int n>
struct Vector
{
    float data[n];

    inline float operator[](int index)
    {
        if (index >= n) throw std::runtime_error("Invalid access\n");
        return data[index];
    }
    inline Vector<n> operator+(Vector<n> other)
    {
        for (int i = 0; i < n; i++) this->data[n] += other[n];
        return *this;
    }
    Vector<n> operator-(Vector<n> other);
    {
        for (int i = 0; i < n; i++) this->data[n] -= other[n];
        return *this;
    }
    float operator*(vec<n> other);
    {
        float total = 0;
        for (int i = 0; i < n; i++) total += this->data[n] * other[n];
        return total;
    }
    Vector<n> operator*(float scalar); // TODO, PARAMETERIZE TYPE
    {
        for (int i = 0; i < n; i++) total += this->data[n] * scalar;
        return *this;
    }

};

template<>
struct Vector<2>
{
    union
    {
        float data[2];
        struct {float x, y;};
    };
};

template<>
struct Vector<3>
{
    union
    {
        float data[3];
        struct {float x, y, z;};
    };
};

template<>
struct Vector<4>
{
    union
    {
        float data[4];
        struct {float x, y, z, w;};
    };
};

typedef Vector<2> vec2;
typedef Vector<3> vec3;
typedef Vector<4> vec4;

// Major column order to comply with OpenGL
// Generic matrix template, might just use mat3 and mat4 since we don't really need much. consider these!
template <int rows, int columns>
struct mat
{
    float data[columns][rows];
};

}