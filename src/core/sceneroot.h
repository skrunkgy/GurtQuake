#pragma once 

#include "gqobject.h"

namespace gquake {

class SceneRoot : public gqObject
{
public:
	SceneRoot();
	~SceneRoot();
	void poke(App& app, GQ_POKE_TYPE poke_type);
};

}
