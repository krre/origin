#pragma once
#include "Graphics/Render/RenderWindow.h"
#include "Graphics/Vulkan/Wrapper/Surface/Surface.h"

class VulkanRenderWindow : public RenderWindow {

public:
    VulkanRenderWindow();
    void swapBuffers() override;
    void saveImage(const std::string& filePath) override;

    Vulkan::Surface* getSurface() const { return surface.get(); }

private:
    std::unique_ptr<Vulkan::Surface> surface;
};
