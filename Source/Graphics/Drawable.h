#pragma once
#include "../Core/Object.h"

class Drawable : Object {

public:
    Drawable();
    virtual void draw(float dt) = 0;
};
