// Outlines the Mesh, which inherits from the RenderObject

#pragma once

#include <vector>
#include "shader.h"
#include "../gtypes.h"

namespace gquake
{

class Mesh : public RenderObject
{
public:

	Mesh();
	Mesh(float_32 vertices[], unsigned int count);
	~Mesh();

	// Serialization would look like this
	// GQ_RETURN_CODE static load(const char* path) {return GQ_SUCCESS;};
	// GQ_RETURN_CODE store(const char* path) {return GQ_SUCCESS;};
	
	// In the case we want to modify the actual array
	std::vector<float_32>& get_vertices();
	void attach_shader(Shader& shader);

	// For inserting into the render queue
	// void poke(); // Inherits the RenderObject poke(), no need to implement (yet)

	// Call this AFTER setting the vertices of the mesh!
	void draw();

private:

	std::vector<float_32> m_vertices;
	Shader m_shader;
	unsigned int m_vbo;
	unsigned int m_vao;
	unsigned int m_vertCount;

};
}
