#pragma once
#include "Singleton.h"
#include "Graphics/GraphicsTypes.h"
#include <vector>

class Context : public Singleton<Context> {

public:
    Context();
    GraphicsBackend getCurrentBackend() const;
    void setCurrentBackend(GraphicsBackend backend);
    const std::vector<GraphicsBackend>& getBackends() const;

private:
    std::vector<GraphicsBackend> backends;
    GraphicsBackend currentBackend = GraphicsBackend::NONE;
};
