#include <functional>

#include "gqtypes.h"
#include "gqobject.h"

using namespace gquake;

// Generic traverse function that takes function object
void GQObject::traverse(App& app, GQ_POKE_TYPE poke_type)
{
    if (!m_children.empty())
    {
        for ( GQObject* child : m_children)
        {
            child->traverse(app, poke_type);
        }
    }
	if (poke_type == GQ_DELETE_POKE)
	{
		delete this;
		return;
	}
    poke(app, poke_type);
}

void GQObject::add_child(GQObject* child)
{
	m_children.push_back(child);
}

void GQObject::pop_child(int index)
{
	m_children.erase(m_children.cbegin() + index);
}
