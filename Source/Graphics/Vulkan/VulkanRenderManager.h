#pragma once
#include "Graphics/render/RenderManager.h"

namespace Vulkan {
    class Instance;
}

class VulkanRenderManager : public RenderManager {

public:
    VulkanRenderManager();
    RenderWindow* createRenderWindow() override;

private:
    std::unique_ptr<Vulkan::Instance> vulkan;
};
