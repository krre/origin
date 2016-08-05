#pragma once
#include "../Drawable.h"
#include "../UI/Rectangle.h"

class RenderSurface : public Drawable {

public:
    RenderSurface();
    ~RenderSurface();
    void draw(float dt) override;

private:
    void onWindowResize(int width, int height);
    Rectangle rectangle;
    uint32_t* data;
    uint32_t* depth;
};
