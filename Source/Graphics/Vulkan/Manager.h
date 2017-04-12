#pragma once
#include "../../Core/Singleton.h"
#include "Instance.h"
#include "Swapchain.h"
#include "RenderPass.h"
#include "Command/CommandPool.h"
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

private:
    void onWindowResize(int width, int height);

    std::shared_ptr<CommandPool> commandPool;
    std::shared_ptr<Swapchain> swapchain;
    std::shared_ptr<RenderPass> renderPass;
    Device* device;
};

} // Vulkan
