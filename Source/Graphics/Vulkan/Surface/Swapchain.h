#pragma once
#include "../Base/Handle.h"
#include "../Device/Devicer.h"
#include <vector>

namespace Vulkan {

class Surface;
class Semaphore;

class Swapchain : public Handle<VkSwapchainKHR>, public Devicer {

public:
    Swapchain(Device* device, Surface* surface);
    ~Swapchain();
    void create() override;
    void destroy() override;

    size_t getCount() const { return images.size(); }
    VkImage getImage(size_t i) const { return images.at(i); }
    const std::vector<VkImage>& getImages() const { return images; }
    VkFormat getImageFormat() const { return createInfo.imageFormat; }
    VkResult acquireNextImage(Semaphore* semaphore);
    VkResult acquireNextImage(Semaphore* semaphore, uint32_t* index);
    void setImageIndexPtr(uint32_t* pImageIndex);
    VkImage getCurrentImage() const { return images.at(*pImageIndex); }
    uint32_t getImageIndex() const { return *pImageIndex; }
    void resize(uint32_t width, uint32_t height);

private:
    VkSwapchainCreateInfoKHR createInfo = {};
    Surface* surface;
    std::vector<VkImage> images;
    uint32_t* pImageIndex;
    VkExtent2D oldExtent = { (uint32_t)-1, (uint32_t)-1 };
};

} // Vulkan
