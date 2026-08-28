#include <stdio.h>

#include "sceneroot.h"

using namespace gquake;

SceneRoot::SceneRoot() {}

SceneRoot::~SceneRoot()
{
    printf("SceneRoot destroyed\n");
}
