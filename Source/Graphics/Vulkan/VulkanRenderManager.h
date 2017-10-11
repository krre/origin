#pragma once
#include "Graphics/Render/RenderManager.h"

namespace Vulkan {
    class Instance;
}

class VulkanRenderManager : public RenderManager {

public:
    VulkanRenderManager();
    ~VulkanRenderManager();
    std::shared_ptr<RenderWindow> createRenderWindow() override;
    void setClearColor(const Color& color) override;
    void clear() override;

    Vulkan::Instance* getVulkanInstance() const { return vulkanInstance.get(); }

private:
    std::unique_ptr<Vulkan::Instance> vulkanInstance;
};
