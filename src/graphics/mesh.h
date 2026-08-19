// mesh.h || Outlines the Mesh, which inherits from the RenderObject

#pragma once

#include <initializer_list>
#include <cassert>
#include "../math/math.h"
#include "../graphics/renderobject.h"
#include "../core/gqtypes.h"
#include "shader.h"

#define ATTRIB_COUNT 5 // basically how many floats in a vertice

namespace gquake
{

// Quick note on the Vertex...
// I was planning on doing separate buffers for the positions, normals etc, but I might just do this instead. I MAY still do an indexed buffer, but those aren't very hard to configure.


struct Vertex
{
	vec3 position; 
	vec2 uv;
	// vec3 normal;
	// float_32[8] other; // do not use
	
	// these constructors are only for position data
	Vertex() {
		this->position = vec3();
		this->uv = vec2();
	}
	Vertex(vec3 _pos, vec2 _uv)
	{
		this->position = _pos;
		this->uv = _uv;
	}
	Vertex(std::initializer_list<float32_t> _data)
	{
		// This looks nasty, but I wonder how common code like this is
		assert(_data.size() <= ATTRIB_COUNT);
		AUTOFOR(i, ATTRIB_COUNT)
		{
			reinterpret_cast<float*>(this)[i] = i >= _data.size() ? 0 : *(_data.begin() + i);
			// ternary assignment here, in case we didnt give enough data
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
	void attach_shader(Shader* shader);

	void _render(App* app); // Inherits the RenderObject poke(), no need to implement (yet)

	// Call this AFTER setting the vertices of the mesh!
	void draw();

private:
	Shader* m_shader;
	uint32_t m_vao, m_vbo, m_ebo;
	uint32_t m_triCount;
};
}
