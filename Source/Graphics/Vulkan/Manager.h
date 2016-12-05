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
#include "PipelineLayout.h"
#include "Pipeline.h"
#include "RenderPass.h"
#include "Framebuffer.h"
#include "CommandPool.h"
#include "CommandBuffer.h"
#include "Collection/CommandBufferCollection.h"
#include "Fence.h"
#include "Semaphore.h"
#include <string>
#include <vector>

const std::string initError = "Vulkan initialization error:\n";

namespace Vulkan {

class Manager : public Singleton<Manager> {

public:
    Manager();
    ~Manager();
    bool createInstance();
    bool init();
    Vulkan::Instance* getInstance() const { return instance; }
    Vulkan::Device* getDevice() const { return device; }
    Vulkan::Surface* getSurface() const { return surface; }
    void drawFrame();

private:
    Vulkan::Instance* instance;
    VkPhysicalDevice basePhysicalDevice;
    Vulkan::DebugReportCallback* debugCallback;
    Vulkan::PhysicalDeviceCollection* physicalDeviceCollection;
    Vulkan::Device* device;
    Vulkan::Surface* surface;
    Vulkan::Swapchain* swapchain;
    Vulkan::PipelineLayout* pipelineLayout;
    Vulkan::Pipeline* graphicsPipeline;
    Vulkan::RenderPass* renderPass;
    std::vector<std::shared_ptr<Vulkan::ImageView>> imageViews;
    std::vector<std::shared_ptr<Vulkan::Framebuffer>> framebuffers;
    Vulkan::CommandPool* commandPool;
    Vulkan::CommandBufferCollection* commandBufferCollection;
    Vulkan::Fence* fence;
    Vulkan::Semaphore* imageAvailableSemaphore;
    Vulkan::Semaphore* renderFinishedSemaphore;

    SubmitQueue* graphicsQueue;
    PresentQueue* presentQueue;
    uint32_t graphicsFamily;
    uint32_t presentFamily; // TODO: Find and use
    uint32_t swapchainImageIndex;
};

} // Vulkan
