#pragma once
#include "../../Core/Object.h"

class RenderSurface;

class OctreeRenderer : public Object {

public:
    OctreeRenderer();
    void render(const RenderSurface* renderSurface);
};
