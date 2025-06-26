#include <gmath.h>
#include <stdio.h>

using namespace gQuake;

int main()
{
	Vector<2, float> a = {1.0, 0.0};
	Vector<2, float> b = {1.0, 0.0};
	Vector<2, float> c = a + b;
	printf("(%f, %f)", c.data[0], c.data[1]);
}