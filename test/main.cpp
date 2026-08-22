// Suite for testing parts of my code, like classes and functions/methods

#include <stdio.h>
#include "../src/math/math.h"

using namespace gquake;

int main()
{
	
	Transform test;
	test.basis = {
		1.0, 0.0, 0.0,
		0.0, 1.0, 0.0,
		0.0, 0.0, 1.0
	};
	test.position = {10, 11, 12};

	Transform b;
	b.position = {2, 1, 0};

	print_mat((test * b).matrix());
	
	return 0;
}
