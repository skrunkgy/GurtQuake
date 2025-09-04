#pragma once

#include <stdio.h>

enum GQ_RETURN_CODE
{
	GQ_SUCCESS,
	GQ_ERR
};

typedef unsigned char uint_8;
typedef unsigned short uint_16;
typedef unsigned int uint_32;
typedef unsigned long uint_64;

namespace gQuake
{

// Pure virtual class for data types that can be serialized
class Serialize
{
public:
	virtual ~Serialize() = default;
	virtual GQ_RETURN_CODE Load() = 0;
	virtual GQ_RETURN_CODE Store() = 0;
	unsigned int UID;
};

// An object that can be attached to a render queue and rendered. Can be meshes or GUI (also purely virtual)
class RenderObject
{
public:
	virtual void Render() = 0;
	virtual ~RenderObject() = default;
};

}