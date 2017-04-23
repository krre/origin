#include "Renderer.h"

Renderer::Renderer() {
    vulkan = std::unique_ptr<Vulkan::Instance>(new Vulkan::Instance());
    vulkan->create();
}

void Renderer::render() {

}
