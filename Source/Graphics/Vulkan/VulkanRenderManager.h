#pragma once
#include "Graphics/Render/RenderManager.h"

class VulkanRenderManager : public RenderManager {

public:
    VulkanRenderManager();
    ~VulkanRenderManager();
    std::shared_ptr<RenderWindow> createRenderWindow() override;
};
