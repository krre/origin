#pragma once
#include "../base/Handle.h"
#include "../device/Devicer.h"
#include <vector>

namespace Vulkan {

class Surface;
class Semaphore;

class Swapchain : public Handle<VkSwapchainKHR>, public Devicer {
public:
    Swapchain(Device* device, Surface* surface);
    ~Swapchain();

    void create() override;
    void destroy();

    size_t count() const { return m_images.size(); }
    VkImage image(size_t i) const { return m_images.at(i); }
    const std::vector<VkImage>& images() const { return m_images; }
    VkFormat imageFormat() const { return m_createInfo.imageFormat; }
    VkResult acquireNextImage(Semaphore* semaphore);
    VkResult acquireNextImage(Semaphore* semaphore, uint32_t* index);
    void setImageIndexPtr(uint32_t* pImageIndex);
    VkImage currentImage() const { return m_images.at(*m_imageIndex); }
    uint32_t imageIndex() const { return *m_imageIndex; }

private:
    VkSwapchainCreateInfoKHR m_createInfo = {};
    Surface* m_surface = nullptr;
    std::vector<VkImage> m_images;
    uint32_t* m_imageIndex = nullptr;
    VkExtent2D m_oldExtent = { (uint32_t)-1, (uint32_t)-1 };
};

}
