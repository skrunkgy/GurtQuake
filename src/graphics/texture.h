// texture.h || Class that wraps the textures

#pragma once 

#include "../core/gqtypes.h"

namespace gquake
{

// Perhaps make this virtual?
class Texture2D
{
public:
	Texture2D();
	~Texture2D();

	void load_path();
private:
	uint32_t m_texture;
};

} // namespace gquake
