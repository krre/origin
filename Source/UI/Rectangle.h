#pragma once
#include "../Graphics/Drawable.h"

class Rectangle : Drawable {

public:
    Rectangle();
    void draw(float dt) override;
};
