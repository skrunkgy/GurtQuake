#include "gtypes.h"

using namespace gQuake;


Serialize::Serialize() {}

void Serialize::Store(const char* filepath)
{}

template <class gq_Class>
gq_Class* Serialize::Load(const char* filepath)
{
    gq_Class *obj = new gq_Class();
    obj->Load(filepath);
    return obj;
}

