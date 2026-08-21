// Suite for testing parts of my code, like classes and functions/methods

#include <stdio.h>
#include "../src/math/math.h"

using namespace gquake;

int main()
{
	Transform parent;

	parent.rotate_axis(PI / 2, vec3(0, 0, 1));
	parent.position += vec3(0, 1, 0);
	vec4 point = parent.get_matrix() * vec4(1.0, 0.0, 0.0, 1.0);

	print_vec(point);
	
	return 0;
}
