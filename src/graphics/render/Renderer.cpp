#include "Renderer.h"
#include "RenderManager.h"

Renderer::Renderer(Object* parent) : Object(parent) {
    m_device = RenderManager::get()->getGraphicsDevice();
}

Renderer::~Renderer() {

}

void Renderer::setActive(bool active) {
    this->m_active = active;
}
