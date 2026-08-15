#include <functional>

#include "gqtypes.h"
#include "gqobject.h"

using namespace gquake;

// Generic traverse function that takes function object
void GQObject::traverse(PokeData poke)
{
    if (!m_children.empty())
    {
        for ( GQObject* child : m_children)
        {
            child->traverse(poke);
        }
    }
	switch (poke.type)
	{
		default:
			return;
		case GQ_LOGIC_POKE:
			this->_loop(poke.dt);
			break;
		case GQ_RENDER_POKE:
			this->_render(poke.app);
			break;
		case GQ_INPUT_POKE:
			this->_input(*poke.event);
			break;
		case GQ_DELETE_POKE:
			delete this;
			break;
	}
}

void GQObject::add_child(GQObject* child)
{
	child->_enter(); // I guess this works, for now?
	m_children.push_back(child);
}

void GQObject::pop_child(int index)
{
	m_children.erase(m_children.cbegin() + index);
}
