#pragma once

#include <vector>
#include "shader.h"
#include "../gtypes.h"

namespace gQuake
{

class Mesh : public RenderObject
{

public:

	Mesh();
	Mesh(float vertices[], unsigned int count);
	~Mesh();

	// For serialization
	// GQ_RETURN_CODE load() {return GQ_SUCCESS;};
	// GQ_RETURN_CODE store() {return GQ_SUCCESS;};
	// void load(const char* filepath);

	// In the case we want to modify the actual array!
	std::vector<float>& get_vertices();
	void setup();
	void attach_shader(Shader& shader);

	// For inserting into the render queue
	// void poke(); // Inherits the RenderObject poke(), no need to implement (yet)

	// Call this AFTER setting the vertices of the mesh!
	void set_attrib_layout(std::initializer_list<int> counts);
	void draw();

private:

	std::vector<float> m_vertices;
	Shader m_shader;
	unsigned int m_vbo;
	unsigned int m_vao;
	unsigned int m_vertCount;

};

}