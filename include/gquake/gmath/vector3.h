#include "qualifier.h"

namespace gquake
{

template<typename T>
struct vec<3, T>
{
	union
	{
		struct {T x, y, z; };
		struct {T r, g, b; };
		struct {T u, v, s; };
	};

	vec() { x = T(0); y = T(0); z = T(0); }
	vec(T _x, T _y, T _z) { this->x =  _x; this->y =  _y; this->z = _z; }

	// Assignment
	template<typename U>
	vec<3, T>& operator=(const vec<3, U> &o)
	{
		this->x = o.x;
		this->y = o.y;
		this->z = o.z;
		return *this;
	}

};

}
