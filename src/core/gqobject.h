#pragma once 

#include <vector>
#include "gqtypes.h"

namespace gquake {

class App; // We just need this for now...

// Node for a tree
class gqObject
{
private:
	std::vector<gqObject*> m_children;

public:

	std::string name; // Make gqID in the future, struct
	
	virtual ~gqObject() = default;
	virtual void poke(App& app, GQ_POKE_TYPE poke_type) = 0;

	void add_child(gqObject* child);
	void pop_child(int index);
	void traverse(std::function<void(gqObject*, GQ_POKE_TYPE)> func, GQ_POKE_TYPE poke_type); // Method to perform on each node
	void free(); // An inline method that makes use of traverse
};

}

