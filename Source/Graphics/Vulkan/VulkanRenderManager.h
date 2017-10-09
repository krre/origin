#pragma once
#include "Graphics/Render/RenderManager.h"

namespace Vulkan {
    class Instance;
}

class VulkanRenderManager : public RenderManager {

public:
    VulkanRenderManager();
    ~VulkanRenderManager();
    RenderWindow* createRenderWindow() override;

private:
    std::unique_ptr<Vulkan::Instance> vulkan;
};
