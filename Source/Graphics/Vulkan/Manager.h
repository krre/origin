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
    DescriptorPool* getDescriptorPool() const { return descriptorPool; }
    CommandPool* getCommandPool() const { return commandPool; }
    void setCommandBuffers(uint32_t count, const VkCommandBuffer* data);
    void render();

private:
    Instance* instance = nullptr;
    VkPhysicalDevice mainPhysicalDevice;
    DebugReportCallback* debugCallback = nullptr;
    PhysicalDeviceCollection* physicalDeviceCollection = nullptr;
    Device* device = nullptr;
    Surface* surface = nullptr;
    Swapchain* swapchain = nullptr;
    RenderPass* renderPass = nullptr;
    DescriptorPool* descriptorPool = nullptr;
    DescriptorSetCollection* descriptorSetCollection = nullptr;
    std::vector<std::shared_ptr<Vulkan::ImageView>> imageViews;
    std::vector<std::shared_ptr<Vulkan::Framebuffer>> framebuffers;
    CommandPool* commandPool = nullptr;
    CommandBufferCollection* commandBufferCollection = nullptr;
    Semaphore* imageAvailableSemaphore;
    Semaphore* renderFinishedSemaphore;

    SubmitQueue* graphicsQueue = nullptr;
    PresentQueue* presentQueue = nullptr;
    uint32_t graphicsFamily;
    uint32_t presentFamily; // TODO: Find and use
    uint32_t swapchainImageIndex;
};

} // Vulkan
