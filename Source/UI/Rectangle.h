#pragma once
#include "Control.h"
#include "../Graphics/Color.h"

class Rectangle : public Control {

public:
    Rectangle(const Size& size);
    Rectangle(const Pos2& position, const Size& size);

    void setColor(const Color& color);
    const Color& getColor() const { return color; }

    void draw(float dt) override;
    void update(float dt) override;

private:
    Color color = { 1.0, 1.0, 1.0 };
};
