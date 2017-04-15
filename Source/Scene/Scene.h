#pragma once
#include "../Core/Object.h"
#include <SDL.h>
#include <glm/glm.hpp>
#include <vector>

namespace Vulkan {
    class CommandBuffer;
    class CommandBuffers;
    class Semaphore;
    class SubmitQueue;
    class RenderPass;
}

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

    void setBackgroundColor(const glm::vec4& backgroundColor);
    glm::vec4 getBackgroundColor() const { return backgroundColor; }

    void addCamera(std::shared_ptr<Entity> camera);
    void removeCamera(std::shared_ptr<Entity> camera);
    void clearCameras();

    void setCurrentCamera(std::shared_ptr<Entity> currentCamera);
    std::shared_ptr<Entity> getCurrentCamera() const { return currentCamera; }
    // Swap last to cameras
    void switchCamera();

    bool getIsFullScreen() const { return isFullScreen; }
    Vulkan::SubmitQueue* getQueue() const { return queue.get(); }
    Vulkan::Semaphore* getRenderFinishedSemaphore() const { return renderFinishedSemaphore.get(); }
    void setRenderPass(Vulkan::RenderPass* renderPass);

    virtual void setVisible(bool visible);
    bool getVisible() const { return visible; }

protected:
    virtual void writeCommands(Vulkan::CommandBuffer* commandBuffer) = 0;
    virtual void onWindowResize(int width, int height) = 0;
    virtual void onKeyPressed(const SDL_KeyboardEvent& event) {}
    bool isFullScreen = true;
    bool visible = true;
    std::shared_ptr<Vulkan::CommandBuffers> commandBuffers;
    std::shared_ptr<Vulkan::SubmitQueue> queue;
    std::shared_ptr<Vulkan::Semaphore> renderFinishedSemaphore;

private:
    Vulkan::RenderPass* renderPass = nullptr;
    std::shared_ptr<Entity> currentCamera;
    std::shared_ptr<Entity> switchCameras[2];
    glm::vec4 backgroundColor;
    std::vector<std::shared_ptr<Entity>> cameras;
};
