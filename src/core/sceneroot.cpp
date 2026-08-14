#include <iostream>

#include "sceneroot.h"

using namespace gquake;

SceneRoot::SceneRoot() {}

SceneRoot::~SceneRoot()
{
    std::cout << "SceneRoot desotryed\n";
}

void SceneRoot::poke(App& app, GQ_POKE_TYPE poke_type) {}
