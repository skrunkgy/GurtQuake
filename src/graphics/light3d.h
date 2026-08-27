// light3d.h || Represents a Light in 3D of various types.

#pragma once

#include "../core/gqobject.h"
#include "../math/math_types.h"

#define PLIGHT_SIZE 32
#define DLIGHT_SIZE 32

namespace gquake
{

// unused for now
// enum GQ_LIGHT_TYPE
// {
// 	GQ_POINT_LIGHT,
// 	GQ_SUN_LIGHT
// };

class PointLight : public GQObject
{
public:
	PointLight();
	~PointLight();

	void _render(RenderInfo rInfo);
	
	vec3 color;
	float32_t exponent;
	float32_t brightness;
};

class SunLight : public GQObject
{
public:
	SunLight();
	~SunLight();

	void _render(RenderInfo rInfo);

	vec3 color;
	float32_t brightness;
};

} // namespace gquake
