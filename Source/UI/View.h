#pragma once
#include "Control.h"

namespace Vulkan {
    class Device;
    class Semaphore;
    class SubmitQueue;
    class CommandBuffers;
}

class Scene;

class View : public Control {

public:
    View();
    ~View();
    void update(float dt);
    void draw(float dt);
    void render();
    Scene* getScene() const { return scene.get(); }
    Vulkan::Semaphore* getRenderFinishedSemaphore() const { return renderFinishedSemaphore.get(); }
    void resize(uint32_t width, uint32_t height);

protected:
    Vulkan::Device* device;

private:
    std::shared_ptr<Scene> scene; // TODO: Use unique_ptr
    std::unique_ptr<Vulkan::Semaphore> renderFinishedSemaphore;
    std::unique_ptr<Vulkan::SubmitQueue> submitQueue;
    std::shared_ptr<Vulkan::CommandBuffers> commandBuffers; // TODO: Use unique_ptr
};
