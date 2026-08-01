#include "qualifier.h"

namespace gquake
{

template<typename T>
struct vec<2, T>
{
	union
	{
		struct {T x, y;};
		struct {T r, g;};
		struct {T u, v;};
	};
	
	// Constructors
	vec() { x = T(0); y = T(0); }
	vec(vec<2, T> const& o) { x = o.x; y = o.y; }
	vec(T _x, T _y) { x = _x; y = _y; }
	
};

}
