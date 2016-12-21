#pragma once
#include "../../Core/Singleton.h"
#include "Instance.h"
#include "DebugReportCallback.h"
#include "Collection/PhysicalDeviceCollection.h"
#include "Device.h"
#include "Surface.h"
#include "Queue/PresentQueue.h"
#include "Queue/SubmitQueue.h"
#include "Swapchain.h"
#include "ImageView.h"
#include "RenderPass.h"
#include "DescriptorPool.h"
#include "Collection/DescriptorSetCollection.h"
#include "Framebuffer.h"
#include "CommandPool.h"
#include "CommandBuffer.h"
#include "Collection/CommandBufferCollection.h"
#include "Semaphore.h"
#include <string>
#include <vector>

const std::string initError = "Vulkan initialization error:\n";

namespace Vulkan {

class Manager : public Singleton<Manager> {

public:
    Manager();
    ~Manager();
    bool init();
    Instance* getInstance() const { return instance; }
    Device* getDevice() const { return device; }
    Surface* getSurface() const { return surface; }
    Swapchain* getSwapchain() const { return swapchain; }
    RenderPass* getRenderPass() const { return renderPass; }
    void render();

private:
    Instance* instance;
    VkPhysicalDevice mainPhysicalDevice;
    DebugReportCallback* debugCallback;
    PhysicalDeviceCollection* physicalDeviceCollection;
    Device* device;
    Surface* surface;
    Swapchain* swapchain;
    RenderPass* renderPass;
    DescriptorPool* descriptorPool;
    DescriptorSetCollection* descriptorSetCollection;
    std::vector<std::shared_ptr<Vulkan::ImageView>> imageViews;
    std::vector<std::shared_ptr<Vulkan::Framebuffer>> framebuffers;
    CommandPool* commandPool;
    CommandBufferCollection* commandBufferCollection;
    Semaphore* imageAvailableSemaphore;
    Semaphore* renderFinishedSemaphore;

    SubmitQueue* graphicsQueue;
    PresentQueue* presentQueue;
    uint32_t graphicsFamily;
    uint32_t presentFamily; // TODO: Find and use
    uint32_t swapchainImageIndex;
};

} // Vulkan
