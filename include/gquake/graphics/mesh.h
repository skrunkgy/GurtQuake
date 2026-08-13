// Outlines the Mesh, which inherits from the RenderObject

#pragma once

#include <initializer_list>
#include "../gmath.h"
#include "../gtypes.h"
#include "shader.h"

#define ATTRIB_COUNT 3

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
};


class Mesh : public RenderObject
{
public:
	Mesh();
	Mesh(Vertex vertices[], unsigned int count);
	Mesh(std::initializer_list<Vertex> vertices);
	~Mesh();

	Transform transform;

	// Serialization would look like this
	// GQ_RETURN_CODE static load(const char* path) {return GQ_SUCCESS;};
	// GQ_RETURN_CODE store(const char* path) {return GQ_SUCCESS;};
	
	// In the case we want to modify the actual array
	void attach_shader(Shader& shader);
	
	void poke(App& app, GQ_POKE_TYPE poke_type); // Inherits the RenderObject poke(), no need to implement (yet)

	// Call this AFTER setting the vertices of the mesh!
	void draw();

private:
	Shader m_shader;
	unsigned int m_vbo;
	unsigned int m_vao;
	unsigned int m_vertCount;

};
}
