// gqobject.h || Outlines the GQObject class, which is our base class for all of the actors

#pragma once 

#include <vector>
#include <string>

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
	virtual void poke(App& app, GQ_POKE_TYPE poke_type) = 0;

	void add_child(GQObject* child);
	void pop_child(int index);
	void traverse(App& app, GQ_POKE_TYPE poke_type); // Method to perform on each node
};

}

