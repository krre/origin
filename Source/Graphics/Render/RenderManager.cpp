#include "RenderManager.h"
#include "Origin.h"

RenderManager::RenderManager() {
    backends.push_back(GraphicsBackend::OPENGL);
#ifdef VULKAN_BACKEND
    backends.push_back(GraphicsBackend::VULKAN);
#endif
}

GraphicsBackend RenderManager::getCurrentBackend() const {
    return currentBackend;
}

void RenderManager::setCurrentBackend(GraphicsBackend backend) {
    currentBackend = backend;
}

const std::vector<GraphicsBackend>&RenderManager::getBackends() const {
    return backends;
}
