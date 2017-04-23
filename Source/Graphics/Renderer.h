#pragma once
#include "Core/Singleton.h"
#include "Vulkan/Instance.h"

namespace Vulkan {
    class Instance;
}

class Renderer : public Singleton<Renderer> {

public:
    Renderer();
    void render();

private:
    std::unique_ptr<Vulkan::Instance> vulkan;
};
