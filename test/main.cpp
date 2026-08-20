// Suite for testing parts of my code, like classes and functions/methods

#include <stdio.h>
#include "../src/math/math.h"

using namespace gquake;

int main()
{
	mat3x3 m = 
	{
		1, 0, 0,
		0, 1, 0,
		1, 2, 1,
	};
	vec3 v = {4, 3, 1};

	vec3 result = v * m;
	print_vec(result);
	
	return 0;
}
