#include "Renderer.h"
#include "RenderManager.h"

Renderer::Renderer(Object* parent) : Object(parent) {
    device = RenderManager::get()->getGraphicsDevice();
}

Renderer::~Renderer() {

}

void Renderer::setActive(bool active) {
    this->active = active;
}
