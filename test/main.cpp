// Suite for testing parts of my code, like classes and functions/methods

#include <stdio.h>
#include "../src/math/math.h"
#include "../src/core/gqobject.h"

using namespace gquake;

int main()
{
	GQObject parent;
	GQObject child;

	parent.transform.rotate_axis(PI, vec3(0, 0, 1));
	parent.transform.position = vec3(0, -1, 0);
	child.transform.position = vec3(0, 2, 0);

	parent.add_child(&child);
	
	parent.t_set_global();
	parent.traverse({
		.type = GQ_LOGIC_POKE,
		.dt = 0
	});

	vec4 point = vec4(1.0, 0.0, 0.0, 1.0);

	print_mat(child.get_global().get_matrix());
	
	return 0;
}
