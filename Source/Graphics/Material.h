#pragma once
#include "../Core/Object.h"
#include "Color.h"

class Material : public Object {

public:
    Material();

    Color getColor() const { return color; }
    void setColor(const Color& color);

private:
    Color color;
};
