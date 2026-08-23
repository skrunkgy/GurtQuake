// Suite for testing parts of my code, like classes and functions/methods

#include <stdio.h>
#include "../src/math/math.h"

using namespace gquake;

int main()
{
	
	mat3x2 a = 
	{
		1.0, 2.0,
		0.0, 4.0,
		5.0, 6.0
	};

	print_mat(a.transpose());
	
	return 0;
}
