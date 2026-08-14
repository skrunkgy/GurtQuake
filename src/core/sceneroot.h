// sceneroot.h || Extends the GQObject, used as the root of any scene

#pragma once 

#include "gqobject.h"

namespace gquake {

class SceneRoot : public GQObject
{
public:
	SceneRoot();
	~SceneRoot();
	void poke(App& app, GQ_POKE_TYPE poke_type);
};

}
