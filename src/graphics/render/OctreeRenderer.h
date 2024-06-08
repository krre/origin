#pragma once
#include "Renderer.h"

class View3D;

class OctreeRenderer : public Renderer {
public:
    enum class Type {
        Polygonal,
        Raycast
    };

    OctreeRenderer(Object* parent = nullptr);

    virtual void drawView(View3D* view) = 0;
};
