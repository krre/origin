#pragma once
#include "Renderer.h"

namespace Origin {

class View3D;

class OctreeRenderer : public Renderer {

public:

    enum class Type {
        Polygonal,
        Raycast
    };

    OctreeRenderer(Object* parent = nullptr);
    ~OctreeRenderer();

    virtual void drawView(View3D* view) = 0;

private:

};

} // Origin
