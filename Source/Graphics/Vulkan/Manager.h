#pragma once
#include "../../Core/Singleton.h"
#include "Instance.h"
#include "Command/CommandBuffers.h"
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
    Swapchain* getSwapchain() const { return swapchain.get(); }
    RenderPass* getRenderPass() const { return renderPass.get(); }
    CommandPool* getCommandPool() const { return commandPool.get(); }
    Semaphore* getImageAvailableSemaphore() const { return imageAvailableSemaphore.get(); }
    PresentQueue* getPresentQueue() const { return presentQueue.get(); }
    void renderBegin();
    void renderEnd();
    void saveScreenshot(const std::string& filePath);

private:
    void onWindowResize(int width, int height);

    std::shared_ptr<CommandPool> commandPool;
    std::shared_ptr<Swapchain> swapchain;
    std::shared_ptr<RenderPass> renderPass;
    std::vector<std::shared_ptr<ImageView>> imageViews;
    std::shared_ptr<Semaphore> imageAvailableSemaphore;
    std::shared_ptr<PresentQueue> presentQueue;
    Device* device;
};

} // Vulkan
