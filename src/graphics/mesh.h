// mesh.h || Outlines the Mesh, which inherits from the RenderObject

#pragma once

#include <initializer_list>
#include <cassert>
#include "../graphics/renderobject.h"
#include "../core/gqtypes.h"
#include "shader.h"

#define ATTRIB_COUNT 8 // basically how many floats in a vertice

namespace gquake
{ 

struct Vertex
{
	vec3 position; 
	vec2 uv;
	vec3 normal;
	
	// these constructors are only for position data
	Vertex() {
		this->position = vec3();
		this->uv = vec2();
		this->normal = vec3();
	}
	Vertex(vec3 _pos, vec2 _uv, vec3 _norm)
	{
		this->position = _pos;
		this->uv = _uv;
		this->normal = _norm;
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

struct MeshData
{
	Vertex* vertices;
	uint32_t* indices;

	uint32_t nVerts;
	uint32_t nTris;
};

class Mesh : public RenderObject
{
public:
	Mesh();
	Mesh(MeshData data);
	~Mesh();

	// In the case we want to modify the actual array
	void attach_shader(Shader* shader);

	// Call this AFTER setting the vertices of the mesh!
	void draw();

protected:
	Shader* m_Shader;
private:
	uint32_t m_VAO, m_VBO, m_EBO;
	uint32_t m_TriCount;
};

} // namespace gquake
