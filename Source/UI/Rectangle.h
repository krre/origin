#pragma once
#include "Control.h"

class Rectangle : Control {

public:
    Rectangle();
    void draw(float dt) override;
};
