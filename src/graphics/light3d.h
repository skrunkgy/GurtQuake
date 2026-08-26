// light3d.h || Represents a Light in 3D of various types.

#pragma once

#include "../core/gqobject.h"
#include "../math/math_types.h"

namespace gquake
{

// unused for now
// enum GQ_LIGHT_TYPE
// {
// 	GQ_POINT_LIGHT,
// 	GQ_SUN_LIGHT
// };

// From the shader
struct ShaderSunLightStruct
{
	vec3 direction;
	float brightness;
	vec3 color;
};

struct ShaderPointLightStruct
{
	vec3 position;
	float brightness;
	vec3 color;
	float exponent;
};

class PointLight : public GQObject
{
public:
	PointLight();
	~PointLight();

	void _render(RenderInfo rInfo);

	vec3 color;
	float32_t falloff;
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
