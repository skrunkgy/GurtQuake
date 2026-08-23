#include "gqtypes.h"
#include "gqobject.h"

using namespace gquake;

// Generic traverse function that takes function object
void GQObject::traverse(PokeData poke)
{
    if (!m_Children.empty())
    {
        for ( GQObject* child : m_Children)
        {
			// Update global transforms of children
			if (poke.type == GQ_TRANSFORM_POKE) child->m_GlobalTrans = child->transform * m_GlobalTrans;
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
			this->_render(*poke.rQueue);
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
	m_Children.push_back(child);
}

void GQObject::pop_child(int index)
{
	m_Children.erase(m_Children.cbegin() + index);
}

const Transform& GQObject::get_global() const
{
	return m_GlobalTrans;
}

void GQObject::t_set_global()
{
	m_GlobalTrans = transform; 
}
