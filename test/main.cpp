// Suite for testing parts of my code, like classes and functions/methods

#include "../include/gquake/gmath.h"
#include <stdio.h>

using namespace gquake;

int main()
{
	
	vec3 a(1.0, 2.0, 3.0);
	mat4x4 b = 
	{
		1.0, 2.0, 3.0, 4.0,
		1.0, 1.0, 1.0, 0.0,
		0.0, 0.0, 1.0, 0.0,
		0.0, 0.0, 0.0, 0.0
	};

	printf("%f\n", b[0][3]);
}
