#pragma once
#include "Control.h"

class Rectangle : public Control {

public:
    Rectangle(int width, int height);
    void draw(float dt) override;
    void update(float dt) override;
};
