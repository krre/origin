#include "RenderManager.h"
#include "Origin.h"
#include "Core/Settings.h"
#include <algorithm>

RenderManager::RenderManager() {
    backends.push_back(GraphicsBackend::OPENGL);
#ifdef VULKAN_BACKEND
    backends.push_back(GraphicsBackend::VULKAN);
#endif

    std::string backend = Settings::get()->getValue("gfx_backend");
    if (backend == "opengl") {
        currentBackend = GraphicsBackend::OPENGL;
    } else if (backend == "vulkan") {
        currentBackend = GraphicsBackend::VULKAN;
    }

    if (std::find(backends.begin(), backends.end(), currentBackend) == backends.end()) {
        PRINT(std::string("Graphics backend ") + backend + " is not supported. Set to OpenGL");
        currentBackend = GraphicsBackend::OPENGL;
    }
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
