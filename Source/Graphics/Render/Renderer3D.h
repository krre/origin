#pragma once
#include "Core/Common.h"

namespace Origin {

class View3D;

class Renderer3D {

public:
    Renderer3D();
    virtual ~Renderer3D();
    void render(View3D* view3d);
};

} // Origin
