// gqRenderModel | Mesh data resource

#ifndef GQ_RENDERMODEL_H
#define GQ_RENDERMODEL_H

// #include "../core/class.h"
#include "../core/resource.h"
#include "../math/math.h"
#include "../graphics/rendersystem.h"

struct gqVertex
{
	gqVec3		position;
	uint8_t		color[4];
	gqVec3		normal;
	gqVec2		uv;
};

class gqMeshData : public gqResource
{
private:
	uint32_t			glVAO;
	uint32_t			glEBO;

	uint32_t			triCount;
	uint32_t			vertCount;

	uint32_t*			elements;
	gqVertex*			vertices;

public:

	void				InitRender();

	uint32_t			GetVertCount();
	uint32_t			GetTriCount();

};

// I am not sure how I want to split this. This is a representation to the renderer, but actual mesh data may come from elsewhere?
class gqRenderModel
{
private:

	gqMeshData			meshData;
	gqTransform			transform;

public:

	gqTransform&		GetTransform();

};

#endif
