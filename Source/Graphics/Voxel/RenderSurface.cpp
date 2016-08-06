#include "RenderSurface.h"
#include "../Event/Event.h"

RenderSurface::RenderSurface() : rectangle(800, 480) {
//    rectangle.setColor(glm::vec3(0.9f, 0.7f, 0.5f));
    data = new uint32_t[rectangle.getWidth() * rectangle.getHeight()];
    depth = new uint32_t[rectangle.getWidth() * rectangle.getHeight()];
    Event::getInstance()->windowResize.connect<RenderSurface, &RenderSurface::onWindowResize>(this);
}

RenderSurface::~RenderSurface() {
    delete data;
    delete depth;
}

void RenderSurface::draw(float dt) {
    rectangle.draw(dt);
}

void RenderSurface::onWindowResize(int width, int height) {
    rectangle.resize(width, height);
    delete data;
    delete depth;
    data = new uint32_t[rectangle.getWidth() * rectangle.getHeight()];
    depth = new uint32_t[rectangle.getWidth() * rectangle.getHeight()];
}
