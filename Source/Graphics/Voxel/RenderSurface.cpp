#include "RenderSurface.h"
#include "../Event/Event.h"
#include "../Resource/ResourceManager.h"

RenderSurface::RenderSurface() :
    rectangle(800, 480),
    texture(GL_TEXTURE_2D) {
    data = new uint32_t[rectangle.getWidth() * rectangle.getHeight()];
    depth = new uint32_t[rectangle.getWidth() * rectangle.getHeight()];
    surfaceShaderGroup = ResourceManager::getInstance()->getShaderGroup("SurfaceShaderGroup");

    texture.bind();
    glTexImage2D(texture.getType(), 0, GL_RGB, rectangle.getWidth(), rectangle.getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    texture.unbind();

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
