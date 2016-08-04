#pragma once
#include "../Drawable.h"
#include "../UI/Rectangle.h"

class RenderSurface : public Drawable {

public:
    RenderSurface();
    void draw(float dt) override;

private:
    Rectangle rectangle;
};
