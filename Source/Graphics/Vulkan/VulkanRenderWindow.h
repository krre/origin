#pragma once
#include "Graphics/Render/RenderWindow.h"

class VulkanRenderWindow : public RenderWindow {

public:
    VulkanRenderWindow();
    void swapBuffers() override;
    void saveImage(const std::string& filePath) override;
};
