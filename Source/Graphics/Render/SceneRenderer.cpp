#include "SceneRenderer.h"
#include "Vulkan/GpuBuffer.h"
#include "Resource/RenderPass/RenderPassOctree.h"
#include "Graphics/Render/RenderManager.h"
#include "Base/Window.h"
#include "Base/Game.h"
#include "Octree/Octree.h"
#include <glm/gtc/matrix_transform.hpp>

namespace Origin {

static SceneRenderer* instance = nullptr;

SceneRenderer::SceneRenderer(Object* parent) : Renderer(parent) {
    instance = this;
    renderPassOctree = new RenderPassOctree(RenderManager::get()->getGraphicsDevice(), this);
    Octree* octree = new Octree(Substance(), this);
}

SceneRenderer::~SceneRenderer() {

}

SceneRenderer* SceneRenderer::get() {
    return instance;
}

void SceneRenderer::draw() {
    for (Scene* scene : scenes) {


    }

    glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)Window::get()->getWidth() / Window::get()->getHeight(), 0.1f, 100.0f);
    glm::mat4 view = glm::lookAt(glm::vec3(0, 0, 5), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    glm::mat4 model = glm::mat4(1.0f);
    float rot = 0;
    model = glm::rotate(model, rot, glm::vec3(0.0, 1.0, 0.0)) * glm::rotate(model, rot, glm::vec3(1.0, 1.0, 1.0));

    glm::mat4 mvp = proj * view * model;

    scenes.clear();
}

RenderPassResource* SceneRenderer::getRenderPass() const {
    return renderPassOctree;
}

void SceneRenderer::addScene(Scene* scene) {
    scenes.push_back(scene);
}

} // Origin
