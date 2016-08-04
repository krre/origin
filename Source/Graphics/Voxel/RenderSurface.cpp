#include "RenderSurface.h"

RenderSurface::RenderSurface() : rectangle(800, 480) {
    rectangle.setColor(glm::vec3(0.9f, 0.7f, 0.5f));
    data = new uint32_t[rectangle.getWidth() * rectangle.getHeight()];
}

RenderSurface::~RenderSurface() {
    delete data;
}

void RenderSurface::draw(float dt) {
    rectangle.draw(dt);
}
