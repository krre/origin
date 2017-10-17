#pragma once
#include "Core/Object.h"
#include <SDL.h>
#include <vector>

class Entity;
class Control;

class Scene : public Object {

public:
    Scene();
    ~Scene();
    virtual void init();
    virtual void pause();
    virtual void resume();

    void update(float dt);
    void render(float dt);

    void resize(uint32_t width, uint32_t height);

    void buildCommandBuffers();

    void addCamera(const std::shared_ptr<Entity>& camera);
    void removeCamera(const std::shared_ptr<Entity>& camera);
    void clearCameras();

    void setCurrentCamera(const std::shared_ptr<Entity>& currentCamera);
    std::shared_ptr<Entity> getCurrentCamera() const { return currentCamera; }
    // Swap last to cameras
    void switchCamera();

//    Vulkan::SubmitQueue* getQueue() const { return queue.get(); }
//    Vulkan::Semaphore* getRenderFinishedSemaphore() const { return renderFinishedSemaphore.get(); }
//    void setRenderPass(Vulkan::RenderPass* renderPass);

    void setPosition(const Pos2& position);
    const Pos2& getPosition() const { return position; }

    const Size& getSize() const { return size; }
    void setSize(const Size& size);

    void setRootControl(const std::shared_ptr<Control>& root);
    Control* getRootControl() const { return root ? root.get() : nullptr; }

protected:
//    virtual void writeCommands(Vulkan::CommandBuffer* commandBuffer) = 0;
    virtual void onWindowResize(int width, int height) {}
    virtual void onKeyPressed(const SDL_KeyboardEvent& event) {}

    Pos2 position = { 0, 0 };
    Size size;
//    std::shared_ptr<Vulkan::CommandBuffers> commandBuffers;
//    std::shared_ptr<Vulkan::SubmitQueue> queue;
//    std::shared_ptr<Vulkan::Semaphore> renderFinishedSemaphore;

private:
    std::shared_ptr<Control> root;
//    Vulkan::RenderPass* renderPass = nullptr;
    std::shared_ptr<Entity> currentCamera;
    std::shared_ptr<Entity> switchCameras[2] = { nullptr, nullptr };
    std::vector<std::shared_ptr<Entity>> cameras;
};
