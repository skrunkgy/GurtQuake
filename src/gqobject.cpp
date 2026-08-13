#include <gquake/gquake.h>
#include <functional>
#include <iostream>

using namespace gquake;

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

// For freeing the tree (also a demonstraiton)
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

// Render Object

// Will override all render objects and ones inherited i hope!
void RenderObject::poke(App& app)
{
	app.add_to_render_queue(this);
}

// Scene Root extended type

SceneRoot::SceneRoot() {}

SceneRoot::~SceneRoot()
{
    std::cout << "SceneRoot desotryed\n";
}

void SceneRoot::poke(App& app) {}
