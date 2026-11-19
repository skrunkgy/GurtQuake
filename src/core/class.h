// gqClass | utilities and PERCHANCE base class for all classes later on

#ifndef GQ_CLASS_H
#define GQ_CLASS_H

#include "utils.h"

#define REFLECTION(CLASS)						\
private:										\
	const char* classname = STR(CLASS)			\
// we dont add ; on the last line, so we can do REFLECTION(x);

#endif
