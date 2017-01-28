#pragma once
#include "../../Core/Singleton.h"
#include "Instance.h"
#include "DebugReportCallback.h"
#include "Device/PhysicalDevice.h"
#include "Device/PhysicalDevices.h"
#include "Command/CommandBuffers.h"
#include "Device/Device.h"
#include "Surface.h"
#include "Queue/PresentQueue.h"
#include "Queue/SubmitQueue.h"
#include "Swapchain.h"
#include "Image/ImageView.h"
#include "RenderPass.h"
#include "Framebuffer.h"
#include "Command/CommandPool.h"
#include "Semaphore.h"
#include <string>
#include <vector>

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
    SubmitQueue* getGraphicsQueue() const { return graphicsQueue; }
    uint32_t getGraphicsFamily() const { return graphicsFamily; }
    void setCommandBuffers(uint32_t count, const VkCommandBuffer* data);
    void setCommandBuffers(const CommandBuffers* commandBuffers);
    void renderBegin();
    void renderEnd();
    void submit();
    void saveScreenshot(const std::string& filePath);

private:
    Instance* instance = nullptr;
    PhysicalDevice* mainPhysicalDevice;
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
