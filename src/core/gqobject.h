// gqobject.h || Outlines the GQObject class, which is our base class for all of the actors

#pragma once 

#include <vector>
#include <string>
#include <SDL3/SDL_events.h>

#include "gqtypes.h"

namespace gquake {

class App; // We just need this for now...

// Node for a tree
class GQObject
{
private:
	std::vector<GQObject*> m_children;

public:

	std::string name; // Make gqID in the future, struct
	
	virtual ~GQObject() = default;

	void add_child(GQObject* child);
	void pop_child(int index);
	void traverse(PokeData poke); // Method to perform on each node
	
	template <typename T>
	T* get_child(int index)
	{
		if (m_children.size() <= index) return nullptr;
		return reinterpret_cast<T*>(m_children[index]);
	}
	
	// Functions for different traversal passes
	virtual void _enter() {};
	virtual void _loop(float32_t dt) {};
	virtual void _input(SDL_Event& event) {};
	virtual void _render(App* app) {};
};

} // namespace gquake
