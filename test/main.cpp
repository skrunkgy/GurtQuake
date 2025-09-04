#include "../src/gmath/vector2.h"
#include <stdio.h>

using namespace gQuake;

int main()
{
	vec2f b = {1.0, 0.0};
	vec2f c = vec2f{1.0, 0.0};

	printf("(%f, %f)\n", c.x, c.y);
}