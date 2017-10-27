#pragma once
#include "Common.h"
#include <vector>

class View;

namespace Vulkan {
    class Device;
    class Semaphore;
    class SubmitQueue;
    class CommandBuffer;
    class CommandBuffers;
}


class Screen {

public:
    Screen();
    ~Screen();
    virtual void hide();
    virtual void pause();
    virtual void resume();
    virtual void show();

    void update(float dt);
    void render();
    void resize(uint32_t width, uint32_t height);

    void pushView(const std::shared_ptr<View>& view);
    void popView();
    View* getCurrentView() const { return currentView; }

private:
    void updateRenderViews();

    std::vector<std::shared_ptr<View>> views;
    std::vector<View*> renderViews;
    View* currentView = nullptr;
    bool isPaused = true;

    Vulkan::Device* device;
    std::unique_ptr<Vulkan::Semaphore> renderFinishedSemaphore;
    std::unique_ptr<Vulkan::SubmitQueue> submitQueue;
    std::unique_ptr<Vulkan::CommandBuffers> commandBufferHandlers;
    std::vector<std::unique_ptr<Vulkan::CommandBuffer>> commandBuffers;
};
