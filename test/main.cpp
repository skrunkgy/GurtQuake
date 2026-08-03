// Suite for testing parts of my code, like classes and functions/methods

#include "../include/gquake/gmath.h"
#include <stdio.h>

using namespace gquake;

int main()
{
	
	vec2 test(1.0, 1.0);

	printf("%f\n", (3.0 * test).x); // Prints the first column second row
}
