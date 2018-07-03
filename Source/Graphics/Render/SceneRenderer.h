#pragma once
#include "Renderer.h"

namespace Origin {

class Scene;

class SceneRenderer : public Renderer {

public:

    SceneRenderer(Object* parent = nullptr);
    ~SceneRenderer();

    void writeCommandBuffer(Vulkan::CommandBuffer* commandBuffer, Vulkan::Framebuffer* framebuffer) override;

    static SceneRenderer* get();

    void draw() override;
    bool getActive() const override;

    void addScene(Scene* scene);
    void clearScenes();

private:
    std::vector<Scene*> scenes;
};

} // Origin
