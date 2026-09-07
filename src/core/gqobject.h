// gqobject.h || Outlines the GQObject class, which is our base class for all of the actors

#pragma once 

#include <vector>
#include <queue>
#include <string>
#include <functional>
#include <SDL3/SDL_events.h>

#include "gqtypes.h"
#include "../math/transform.h"

namespace gquake {

class RenderObject; // We just need this for now...

struct RenderTarget
{
	std::queue<RenderObject*> drawQueue;
	// std::queue<Light*> lightQueue;
	// Camera* camera;
};

// Node for a tree
class GQObject
{
private:
	std::vector<GQObject*> m_Children;
	GQObject* m_Parent = nullptr;
	Transform m_GlobalTrans;

public:

	friend class App;

	std::string name; // Make gqID in the future, struct
	Transform transform;
	
	virtual ~GQObject() = default;

	void add_child(GQObject* child);
	void pop_child(int index);
	void traverse(std::function<void(GQObject*)> func); // Method to perform on each node
	
	template <typename T>
	T* get_child(int index);
	template <typename T = GQObject>
	T* get_parent();

	void t_set_global();

	const Transform& get_global() const;
	
	// Functions for different traversal passes
	virtual void _enter() {};
	virtual void _loop(float32_t dt) {};
	virtual void _input(SDL_Event& event) {};
	virtual void _render(RenderInfo rTarget) {};
};

} // namespace gquake
