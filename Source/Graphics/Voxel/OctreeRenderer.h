#pragma once
#include "../../Core/Object.h"

class RenderSurface;

class OctreeRenderer : public Object {

public:
    OctreeRenderer();
    void render();
    void setRenderSurface(RenderSurface* renderSurface);

private:
    RenderSurface* renderSurface;
};
