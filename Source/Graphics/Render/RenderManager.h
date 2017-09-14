#pragma once
#include "Graphics/GraphicsTypes.h"
#include <vector>

class RenderManager {

public:
    RenderManager();
    GraphicsBackend getCurrentBackend() const;
    void setCurrentBackend(GraphicsBackend backend);
    const std::vector<GraphicsBackend>& getBackends() const;

private:
    std::vector<GraphicsBackend> backends;
    GraphicsBackend currentBackend = GraphicsBackend::OPENGL;
};
