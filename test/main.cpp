// Suite for testing parts of my code, like classes and functions/methods

#include "../src/math/math.h"
#include "../src/math/transform.h"
#include "../src/math/functions.h"
#include <stdio.h>

using namespace gquake;

int main()
{
	
	// Transform test;
	// test.rotate_axis(3.14159, {1.f, 0.f, 0.f});

	mat3x3 a = {
		1.f, 0.f, 0.f,
		0.f, 1.f, 0.f,
		0.f, 0.f, 1.f
		};

	a[0] = vec3(2.f, 1.f, 3.f);
	
	printf("%f\n", dot(vec3(0.f, 1.f, 0.f), vec3(0.f, -1.f, 0.f)));

}
