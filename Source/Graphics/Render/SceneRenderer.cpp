#include "SceneRenderer.h"
#include "ECS/Scenes/Scene.h"
#include "Octree/Octree.h"

namespace Origin {

static SceneRenderer* instance = nullptr;

SceneRenderer::SceneRenderer(Object* parent) : Origin::Renderer(parent) {
    instance = this;

    Octree* octree = new Octree(Substance(), this);
}

SceneRenderer::~SceneRenderer() {

}

void SceneRenderer::writeCommandBuffer(Vulkan::CommandBuffer* commandBuffer, Vulkan::Framebuffer* framebuffer) {

}

SceneRenderer* SceneRenderer::get() {
    return instance;
}

void SceneRenderer::draw() {
    for (Scene* scene : scenes) {


    }
}

bool SceneRenderer::getActive() const {
    return scenes.size() > 0;
}

void SceneRenderer::addScene(Scene* scene) {
    scenes.push_back(scene);
}

void SceneRenderer::clearScenes() {
    scenes.clear();
}

} // Origin
