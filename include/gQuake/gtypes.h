#pragma once

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

// Pure virtual class for data types that can be serialized
class gqObject
{
public:
	virtual ~gqObject() = default;
	virtual GQ_RETURN_CODE Load() = 0;
	virtual GQ_RETURN_CODE Store() = 0;
	unsigned int UID;
};

// An object that can be attached to a render queue and rendered. Can be meshes or GUI (also purely virtual)
class RenderObject : public gqObject
{
public:
	virtual void Render() = 0;
	virtual ~RenderObject() = default;
};

}