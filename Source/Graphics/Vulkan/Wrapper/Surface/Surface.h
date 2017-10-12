#pragma once
#include "../Base/Handle.h"
#include <vector>

namespace Vulkan {

class Swapchain;

class Surface : public Handle<VkSurfaceKHR> {

public:
    Surface(VkInstance instance, VkPhysicalDevice physicalDevice);
    ~Surface();
    void create() override;
    void destroy() override;

    const std::vector<VkSurfaceFormatKHR>& getFormats() const { return formats; }
    const std::vector<VkPresentModeKHR>& getPresentModes() const { return presentModes; }
    const VkSurfaceCapabilitiesKHR& getCapabilities() const { return capabilities; }
    VkExtent2D getCurrentExtent() const;
    Swapchain* getSwapchain() const { return swapchain.get(); }

protected:
    virtual void platformCreateHandle() = 0;
    VkInstance instance;

private:
    VkPhysicalDevice physicalDevice;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
    VkSurfaceCapabilitiesKHR capabilities;
    std::unique_ptr<Swapchain> swapchain;
};

} // Vulkan
