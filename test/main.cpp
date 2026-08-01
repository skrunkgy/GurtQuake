// Suite for testing parts of my code, like classes and functions/methods

#include "../include/gquake/gmath.h"
#include <stdio.h>

using namespace gquake;

int main()
{
	vec2 a = {0, 0};
	vec2 b = {1, 1};

	vec2 c = b * 4;

	printf("(%f, %f)\n", c.x, c.y);

	//
}
