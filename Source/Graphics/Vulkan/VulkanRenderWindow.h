#pragma once
#include "Graphics/Render/RenderWindow.h"

namespace Vulkan {
    class Surface;
}

class VulkanRenderWindow : public RenderWindow {

public:
    VulkanRenderWindow();
    void swapBuffers() override;
    void saveImage(const std::string& filePath) override;
    void createSurface() override;

    Vulkan::Surface* getSurface() const { return surface.get(); }

private:
    std::unique_ptr<Vulkan::Surface> surface;
};
