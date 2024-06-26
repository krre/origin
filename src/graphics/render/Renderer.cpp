#include "Renderer.h"
#include "RenderManager.h"

Renderer::Renderer(Object* parent) : Object(parent) {
    m_device = RenderManager::get()->graphicsDevice();
}

void Renderer::setActive(bool active) {
    m_active = active;
}
