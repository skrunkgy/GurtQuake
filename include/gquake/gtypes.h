#pragma once

#include <string>
#include <vector>
#include <functional>

enum GQ_RETURN_CODE
{
	GQ_SUCCESS,
	GQ_ERR
};

typedef unsigned char uint_8;
typedef unsigned short uint_16;
typedef unsigned int uint_32;
typedef unsigned long uint_64;
typedef float float32;
typedef double float64;

namespace gQuake
{

// Node for a tree
class gqObject
{
private:
	std::vector<gqObject*> m_children;

public:

	std::string name; // Unused.. for now..

	virtual ~gqObject() = default;
	virtual void poke() = 0;

	void add_child(gqObject* child);
	void pop_child(int index);
	void traverse(std::function<void(gqObject*)> func); // Method to perform on each node
	void free(); // An inline method that makes use of traverse
};

class LevelRoot : public gqObject
{
public:
	LevelRoot();
	~LevelRoot();
	void poke();
};

// An object that can be attached to a render queue and rendered. Can be meshes or GUI (also purely virtual)
class RenderObject : public gqObject
{
public:
	virtual ~RenderObject() = default;
	virtual void draw() = 0;
	void poke();
};

}