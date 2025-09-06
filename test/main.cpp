#include "../src/gmath/gmath.h"
#include <stdio.h>

using namespace gQuake;

int main()
{
	vec2f b = {1.0, 4.0};
	vec2f c = b * 3;

	printf("(%f, %f)\n", c.x, c.y);
}