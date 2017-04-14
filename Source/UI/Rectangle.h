#pragma once
#include "Control.h"

class Rectangle : public Control {

public:
    Rectangle(const Size& size);
    Rectangle(const Pos2& position, const Size& size);

    void draw(float dt) override;
    void update(float dt) override;
};
