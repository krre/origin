#include "Context.h"
#include "Origin.h"
#include "Core/Settings.h"
#include "Core/App.h"
#include "Core/Utils.h"
#include <algorithm>

Context::Context() {
#ifdef ENABLE_OPENGL
    backends.push_back(GraphicsBackend::OPENGL);
#endif

#ifdef ENABLE_VULKAN
    backends.push_back(GraphicsBackend::VULKAN);
#endif

    for (const auto& arg : App::get()->getArgv()) {
        if (arg == "-v") {
            currentBackend = GraphicsBackend::VULKAN;
            break;
        }

        if (arg == "-g") {
            currentBackend = GraphicsBackend::OPENGL;
            break;
        }
    }

    if (currentBackend == GraphicsBackend::NONE) {
        std::string backend = Settings::get()->getValue("gfx_backend");
        if (backend == "opengl") {
            currentBackend = GraphicsBackend::OPENGL;
        } else if (backend == "vulkan") {
            currentBackend = GraphicsBackend::VULKAN;
        }
    }

    if (std::find(backends.begin(), backends.end(), currentBackend) == backends.end()) {
        throw std::runtime_error(std::string("Graphics backend ") + Utils::graphicsBackendToString(currentBackend) + " is not supported");
    }
}

GraphicsBackend Context::getCurrentBackend() const {
    return currentBackend;
}

void Context::setCurrentBackend(GraphicsBackend backend) {
    currentBackend = backend;
}

const std::vector<GraphicsBackend>&Context::getBackends() const {
    return backends;
}
