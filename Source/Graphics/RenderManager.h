#pragma once
#include "Core/Singleton.h"

class Screen;

namespace Vulkan {
    class Semaphore;
    class SubmitQueue;
    class Device;
}

class RenderManager : public Singleton<RenderManager> {

public:
    RenderManager();
    ~RenderManager();
    void renderScreen(Screen* screen, Vulkan::Semaphore* waitSemaphore, Vulkan::Semaphore* signalSemaphore, uint32_t imageIndex);

private:
    Vulkan::Device* device;
    std::unique_ptr<Vulkan::SubmitQueue> submitQueue;
};
