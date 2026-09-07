#include <functional>
#include "gqtypes.h"
#include "gqobject.h"

using namespace gquake;

// Generic traverse function that takes function pointer
void GQObject::traverse(std::function<void(GQObject*)> func)
{
    if (!m_Children.empty())
    {
        for ( GQObject* child : m_Children)
        {
			child->traverse(func);
        }
    }
	func(this);
}

void GQObject::add_child(GQObject* child)
{
	child->m_Parent = this;
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
