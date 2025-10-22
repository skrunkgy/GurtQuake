#include <gQuake/gtypes.h>
#include <functional>
#include <iostream>

namespace gQuake
{

// Generic traverse function that takes function object
void gqObject::traverse(std::function<void(gqObject*)> func)
{
    if (!m_children.empty())
    {
        for ( gqObject* child : m_children)
        {
            child->traverse(func);
        }
    }
    func(this);
}

// For freeing the tree
void gqObject::free()
{
    this->traverse([](gqObject* t){
        delete t;
    });
}

void gqObject::add_child(gqObject* child)
{
    m_children.push_back(child);
}

void gqObject::pop_child(int index)
{
    m_children.erase(m_children.cbegin() + index);
}

LevelRoot::LevelRoot() {}

LevelRoot::~LevelRoot()
{
    std::cout << "LevelRoot desotryed\n";
}

void LevelRoot::poke() {
    std::cout << "Shit\n";
}

}