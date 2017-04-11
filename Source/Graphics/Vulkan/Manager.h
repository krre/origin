#pragma once
#include "../../Core/Singleton.h"
#include "Instance.h"
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
#include "Command/CommandPool.h"
#include "Semaphore.h"
#include <string>
#include <vector>

namespace Vulkan {

class Manager : public Singleton<Manager> {

public:
    ~Manager();
    void init();
    Device* getDevice() const { return device.get(); }
    Surface* getSurface() const { return surface.get(); }
    Swapchain* getSwapchain() const { return swapchain.get(); }
    RenderPass* getRenderPass() const { return renderPass.get(); }
    CommandPool* getCommandPool() const { return commandPool.get(); }
    const PhysicalDevices* getPhysicalDevices() const { return physicalDevices.get(); }
    uint32_t getGraphicsFamily() const { return graphicsFamily; }
    Semaphore* getImageAvailableSemaphore() const { return imageAvailableSemaphore.get(); }
    PresentQueue* getPresentQueue() const { return presentQueue.get(); }
    void renderBegin();
    void renderEnd();
    void saveScreenshot(const std::string& filePath);

private:
    void onWindowResize(int width, int height);

    PhysicalDevice* mainPhysicalDevice;
    std::shared_ptr<PhysicalDevices> physicalDevices;
    std::shared_ptr<Device> device;
    std::shared_ptr<Surface> surface;
    std::shared_ptr<CommandPool> commandPool;
    std::shared_ptr<Swapchain> swapchain;
    std::shared_ptr<RenderPass> renderPass;
    std::vector<std::shared_ptr<ImageView>> imageViews;
    std::shared_ptr<Semaphore> imageAvailableSemaphore;
    std::shared_ptr<PresentQueue> presentQueue;
    uint32_t graphicsFamily;
};

} // Vulkan
