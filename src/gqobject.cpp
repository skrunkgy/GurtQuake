#include <gQuake/gtypes.h>
#include <iostream>

namespace gQuake
{

void gqObject::traverse()
{
    poke();
    if (!m_children.empty())
    {
        for ( gqObject* child : m_children)
        {
            child->traverse();
        }
    }
    else return;
}

// For freeing the tree
void gqObject::free()
{
    if (!m_children.empty())
    {
        for (int i = 0; i < m_children.size(); i++)
        {
            m_children.at(i)->free();
            m_children.erase(m_children.begin() + i);
            
        } //andrw is epicaswomssauke
    }
    delete this;
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

void LevelRoot::poke() {}

}