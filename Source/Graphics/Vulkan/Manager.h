#pragma once
#include "../../Core/Singleton.h"
#include "Instance.h"
#include "DebugReportCallback.h"
#include "PhysicalDevices.h"
#include "Device.h"
#include "Surface.h"
#include "Queue.h"
#include "Swapchain.h"
#include "ImageView.h"
#include "SurfaceFormat.h"
#include "PipelineLayout.h"
#include "Pipeline.h"
#include "RenderPass.h"
#include "Framebuffer.h"
#include "CommandPool.h"
#include "CommandBuffer.h"
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
    bool init();
    bool createSurface();
    std::string getResultDescription() const { return resultDescription; }
    Vulkan::Instance* getInstance() const { return instance; }
    Vulkan::Device* getDevice() const { return device; }
    Vulkan::Surface* getSurface() const { return surface; }
    void drawFrame();

private:
    std::string resultDescription = "None";

    Vulkan::Instance* instance;
    Vulkan::DebugReportCallback* debugCallback;
    Vulkan::PhysicalDevices* physicalDevices;
    Vulkan::Device* device;
    Vulkan::Surface* surface;
    Vulkan::SurfaceFormat* surfaceFormat;
//    Vulkan::Queue* queue;
    Vulkan::Swapchain* swapchain;
    Vulkan::PipelineLayout* pipelineLayout;
    Vulkan::Pipeline* graphicsPipeline;
    Vulkan::RenderPass* renderPass;
    std::vector<std::shared_ptr<Vulkan::ImageView>> imageViews;
    std::vector<std::shared_ptr<Vulkan::Framebuffer>> framebuffers;
    Vulkan::CommandPool* commandPool;
    Vulkan::CommandBuffer* commandBuffer;
    Vulkan::Fence* fence;
    Vulkan::Semaphore* imageAvailableSemaphore;
    Vulkan::Semaphore* renderFinishedSemaphore;

    VkQueue graphicsQueue;
    VkQueue presentQueue;
};

} // Vulkan
