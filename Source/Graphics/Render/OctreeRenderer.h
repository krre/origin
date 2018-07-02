#pragma once
#include "Renderer.h"

namespace Origin {

class OctreeRenderer : public Renderer {

public:

    enum class Type {
        Polygonal,
        Raycast
    };

    OctreeRenderer(Object* parent = nullptr);
    ~OctreeRenderer();

private:

};

} // Origin
