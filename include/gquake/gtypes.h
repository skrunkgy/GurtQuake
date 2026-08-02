// 	Provides the typedefs and some base classes for the engine. Some of this will be rearranged, or the file will be broken up as well. God help.

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
typedef float float_32;
typedef double float_64;

namespace gquake
{

class App;

// Node for a tree
class gqObject
{
private:
	std::vector<gqObject*> m_children;

public:

	std::string name; // Unused.. for now..

	virtual ~gqObject() = default;
	virtual void poke(App* app) = 0;

	void add_child(gqObject* child);
	void pop_child(int index);
	void traverse(std::function<void(gqObject*)> func); // Method to perform on each node
	void free(); // An inline method that makes use of traverse
};

class SceneRoot : public gqObject
{
public:
	SceneRoot();
	~SceneRoot();
	void poke(App* app);
};

// An object that can be attached to a render queue and rendered. Can be meshes or GUI (also MOSTLY purely virtual)
class RenderObject : public gqObject
{
public:
	virtual ~RenderObject() = default;
	virtual void draw() = 0;
	void poke(App* app);
};

}
