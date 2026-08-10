// Suite for testing parts of my code, like classes and functions/methods

#include "../include/gquake/gmath.h"
#include <stdio.h>

using namespace gquake;

int main()
{
	
	vec3 a(1.0, 0.0, 0.0);

	printf("%f\n", rotate_point(a, vec3(0.0, 1.0, 0.0), PI / 2.f)[2]); // Prints the first column second row
}
