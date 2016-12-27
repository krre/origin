#pragma once
#include "../../Core/Singleton.h"
#include "Instance.h"
#include "DebugReportCallback.h"
#include "PhysicalDevices.h"
#include "Command/CommandBufferCollection.h"
#include "Device.h"
#include "Surface.h"
#include "Queue/PresentQueue.h"
#include "Queue/SubmitQueue.h"
#include "Swapchain.h"
#include "ImageView.h"
#include "RenderPass.h"
#include "Framebuffer.h"
#include "Command/CommandPool.h"
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
    CommandPool* getCommandPool() const { return commandPool; }
    Framebuffer* getFramebuffer(int i) { return framebuffers.at(i).get(); }
    PhysicalDevices* getPhysicalDevices() const { return physicalDevices; }
    void setCommandBuffers(uint32_t count, const VkCommandBuffer* data);
    void setCommandBuffers(const CommandBufferCollection* commandBuffers);
    void render();

private:
    Instance* instance = nullptr;
    VkPhysicalDevice mainPhysicalDevice;
    DebugReportCallback* debugCallback = nullptr;
    PhysicalDevices* physicalDevices = nullptr;
    Device* device = nullptr;
    Surface* surface = nullptr;
    Swapchain* swapchain = nullptr;
    RenderPass* renderPass = nullptr;
    std::vector<std::shared_ptr<ImageView>> imageViews;
    std::vector<std::shared_ptr<Framebuffer>> framebuffers;
    CommandPool* commandPool = nullptr;
    Semaphore* imageAvailableSemaphore;
    Semaphore* renderFinishedSemaphore;
    SubmitQueue* graphicsQueue = nullptr;
    PresentQueue* presentQueue = nullptr;
    uint32_t graphicsFamily;
    uint32_t presentFamily; // TODO: Find and use
    uint32_t swapchainImageIndex;
};

} // Vulkan
