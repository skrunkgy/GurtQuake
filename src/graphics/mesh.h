// mesh.h || Outlines the Mesh, which inherits from the RenderObject

#pragma once

#include <initializer_list>
#include <cassert>
#include "../math/math.h"
#include "../graphics/renderobject.h"
#include "../core/gqtypes.h"
#include "shader.h"

#define ATTRIB_COUNT 3 // basically how many floats in a vertice

namespace gquake
{

// Quick note on the Vertex...
// I was planning on doing separate buffers for the positions, normals etc, but I might just do this instead. I MAY still do an indexed buffer, but those aren't very hard to configure.


struct Vertex
{
	vec3 position; 
	// vec2 uv;
	// vec3 normal;
	// float_32[8] other; // do not use
	
	// these constructors are only for position data
	Vertex() {
		this->position = vec3();
	}
	Vertex(vec3 _pos)
	{
		this->position = _pos;
	}
	Vertex(std::initializer_list<float32_t> _data)
	{
		// This looks nasty, but I wonder how common code like this is
		assert(_data.size() == ATTRIB_COUNT);
		AUTOFOR(i, _data.size())
		{
			reinterpret_cast<float*>(this)[i] = *(_data.begin() + i);
		}
	}
};


class Mesh : public RenderObject
{
public:
	Mesh();
	Mesh(Vertex vertices[], uint32_t count);
	Mesh(std::initializer_list<Vertex> vertices);
	~Mesh();

	Transform transform;
	
	// In the case we want to modify the actual array
	void attach_shader(Shader& shader);
	
	void _render(App* app); // Inherits the RenderObject poke(), no need to implement (yet)

	// Call this AFTER setting the vertices of the mesh!
	void draw();

private:
	Shader m_shader;
	unsigned int m_vbo;
	unsigned int m_vao;
	unsigned int m_vertCount;

};
}
