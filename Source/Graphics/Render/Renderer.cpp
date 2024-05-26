#include "Renderer.h"
#include "RenderManager.h"
#include "Vulkan/API/Device/Device.h"

Renderer::Renderer(Object* parent) : Object(parent) {
    device = RenderManager::get()->getGraphicsDevice();
}

Renderer::~Renderer() {

}

void Renderer::setActive(bool active) {
    this->active = active;
}
