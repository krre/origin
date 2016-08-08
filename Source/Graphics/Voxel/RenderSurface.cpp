#include "RenderSurface.h"
#include "../Event/Event.h"
#include "../Resource/ResourceManager.h"

RenderSurface::RenderSurface() : texture(GL_TEXTURE_2D) {
    surfaceShaderGroup = ResourceManager::getInstance()->getShaderGroup("SurfaceShaderGroup");
    Event::getInstance()->windowResize.connect<RenderSurface, &RenderSurface::onWindowResize>(this);
}

RenderSurface::~RenderSurface() {
    delete data;
    delete depth;
}

void RenderSurface::draw(float dt) {
    texture.bind();
    glTexImage2D(texture.getType(), 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    texture.unbind();
}

void RenderSurface::onWindowResize(int width, int height) {
    this->width = width;
    this->height = height;

    if (data != nullptr) {
        delete data;
    }

    if (depth != nullptr) {
        delete depth;
    }

    data = new uint32_t[width * height];
    depth = new uint32_t[width * height];
}
