#pragma once
#include "../Drawable.h"

class RenderSurface : public Drawable {

public:
    RenderSurface();
    void draw(float dt) override;
};
