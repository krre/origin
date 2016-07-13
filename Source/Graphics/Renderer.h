#pragma once
#include "../Core/Object.h"

class Renderer : public Object {

public:
    Renderer();
    void render(float dt);
};
