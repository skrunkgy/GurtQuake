// Suite for testing parts of my code, like classes and functions/methods

#include <stdio.h>
#include "../src/math/math.h"

using namespace gquake;

int main()
{
	Transform parent;
	Transform child;

	parent.position = {2.0, 0.0, 0.0};

	mat4x4 new_transform = child.get_matrix() * parent.get_matrix();
	vec4 position = vec4(0, 0, 0, 1) * new_transform;

	print_vec(position);
	
	return 0;
}
