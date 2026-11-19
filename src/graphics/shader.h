// gqShader | holds shader information

#ifndef GQ_SHADER_H
#define GQ_SHADER_H

#include "../core/resource.h"
#include "../core/types.h"
#include "../math/math.h"

typedef struct gqShaderParams_s
{
	union			color
	{
		struct { unsigned char		r,g,b,a; };
		unsigned char*				data;
	};

} gqShaderParams_t;


class gqShader : public gqResource
{

private:
	uint32_t				program;
	gqShaderParams_t		parameters;

public:

	gqShader();
	~gqShader();

	void					InitEmpty();
	void					Init( const char* filename );
	void					LoadShader();

	void					UseShader();
};

#endif
