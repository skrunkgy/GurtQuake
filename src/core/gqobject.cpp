#include <functional>
#include <iostream>

#include "gqtypes.h"
#include "gqobject.h"

using namespace gquake;

// Generic traverse function that takes function object
void gqObject::traverse(std::function<void(gqObject*, GQ_POKE_TYPE)> func, GQ_POKE_TYPE poke_type)
{
    if (!m_children.empty())
    {
        for ( gqObject* child : m_children)
        {
            child->traverse(func, poke_type);
        }
    }
    func(this, poke_type);
}

// For freeing the tree (also a demonstraiton)
void gqObject::free()
{
    this->traverse([](gqObject* t, GQ_POKE_TYPE poke_type){
        delete t;
    }, GQ_DELETE_POKE);
}

void gqObject::add_child(gqObject* child)
{
	m_children.push_back(child);
}

void gqObject::pop_child(int index)
{
	m_children.erase(m_children.cbegin() + index);
}

// Render Object



// Scene Root extended type


