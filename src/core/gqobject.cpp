#include <functional>
#include <iostream>

#include "gqtypes.h"
#include "gqobject.h"

using namespace gquake;

// Generic traverse function that takes function object
void GQObject::traverse(std::function<void(GQObject*, GQ_POKE_TYPE)> func, GQ_POKE_TYPE poke_type)
{
    if (!m_children.empty())
    {
        for ( GQObject* child : m_children)
        {
            child->traverse(func, poke_type);
        }
    }
    func(this, poke_type);
}

// For freeing the tree (also a demonstraiton)
void GQObject::free()
{
    this->traverse([](GQObject* t, GQ_POKE_TYPE poke_type){
        delete t;
    }, GQ_DELETE_POKE);
}

void GQObject::add_child(GQObject* child)
{
	m_children.push_back(child);
}

void GQObject::pop_child(int index)
{
	m_children.erase(m_children.cbegin() + index);
}

// Render Object



// Scene Root extended type


