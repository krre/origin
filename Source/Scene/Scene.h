#pragma once
#include "Core/Object.h"
#include "Graphics/Color.h"
#include <SDL.h>
#include <vector>

//namespace Vulkan {
//    class CommandBuffer;
//    class CommandBuffers;
//    class Semaphore;
//    class SubmitQueue;
//    class RenderPass;
//}

class Entity;

class Scene : public Object {

public:
    Scene();
    ~Scene();
    virtual void init();
    virtual void pause();
    virtual void resume();

    virtual void update(float dt) = 0;
    virtual void draw(float dt) = 0;

    void buildCommandBuffers();

    void setBackgroundColor(const Color& backgroundColor);
    const Color& getBackgroundColor() const { return backgroundColor; }

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

protected:
//    virtual void writeCommands(Vulkan::CommandBuffer* commandBuffer) = 0;
    virtual void onWindowResize(int width, int height) = 0;
    virtual void onKeyPressed(const SDL_KeyboardEvent& event) {}

    Pos2 position = { 0, 0 };
    Size size;
//    std::shared_ptr<Vulkan::CommandBuffers> commandBuffers;
//    std::shared_ptr<Vulkan::SubmitQueue> queue;
//    std::shared_ptr<Vulkan::Semaphore> renderFinishedSemaphore;

private:
//    Vulkan::RenderPass* renderPass = nullptr;
    std::shared_ptr<Entity> currentCamera;
    std::shared_ptr<Entity> switchCameras[2] = { nullptr, nullptr };
    Color backgroundColor = Color::WHITE;
    std::vector<std::shared_ptr<Entity>> cameras;
};
