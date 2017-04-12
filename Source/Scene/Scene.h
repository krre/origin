#pragma once
#include "../UI/Viewport.h"
#include <SDL.h>

namespace Vulkan {
    class Device;
    class CommandBuffer;
    class CommandBuffers;
    class Semaphore;
    class SubmitQueue;
}

class Scene : public Viewport {

public:
    Scene();
    ~Scene();
    virtual void init();
    virtual void pause();
    virtual void resume();

    virtual void update(float dt) = 0;
    virtual void draw(float dt) = 0;

    void buildCommandBuffers();

    bool getIsFullScreen() const { return isFullScreen; }
    Vulkan::SubmitQueue* getQueue() const { return queue.get(); }
    Vulkan::Semaphore* getRenderFinishedSemaphore() const { return renderFinishedSemaphore.get(); }

protected:
    virtual void writeCommands(Vulkan::CommandBuffer* commandBuffer) = 0;
    virtual void onWindowResize(int width, int height) = 0;
    virtual void onKeyPressed(const SDL_KeyboardEvent& event) {}
    bool isFullScreen = true;
    Vulkan::Device* device;
    std::shared_ptr<Vulkan::CommandBuffers> commandBuffers;
    std::shared_ptr<Vulkan::SubmitQueue> queue;
    std::shared_ptr<Vulkan::Semaphore> renderFinishedSemaphore;
};
