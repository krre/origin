#include "SceneRenderer.h"
#include "Vulkan/GpuBuffer.h"
#include "Resource/RenderLayer/RenderLayerOctree.h"
#include "Graphics/Render/RenderManager.h"
#include "Base/Window.h"
#include "Octree/Octree.h"
#include <glm/gtc/matrix_transform.hpp>

namespace Origin {

static SceneRenderer* instance = nullptr;

SceneRenderer::SceneRenderer(Object* parent) : Renderer(parent) {
    instance = this;
    renderLayerOctree = new RenderLayerOctree(RenderManager::get()->getGraphicsDevice(), this);

    blocks.push_back(0xFF0000FF);


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

    RenderLayerOctree::UBO ubo = {};
    ubo.backgroundColor = glm::vec4(0.9, 1.0, 1.0, 1.0);
    ubo.frameWidth = Window::get()->getWidth();
    ubo.frameHeight = Window::get()->getHeight();
    renderLayerOctree->writeUBO(ubo);
    renderLayerOctree->writeBlocks(0, blocks.data(), blocks.size() * sizeof(uint32_t));

    RenderLayerOctree::MetaData metaData = {};
    metaData.blockIndex = 0;
    metaData.origin = glm::vec3(0.0, 0.0, -5.0);

    glm::vec3 up = glm::vec3(0.0, -1.0, 0.0); // Flip Vulkan coordinate system by setting Y to -1
    glm::vec3 look = glm::vec3(0.0, 0.0, -1.0);
    glm::vec3 right = glm::vec3(1.0, 0.0, 0.0);

    float fov = glm::radians(50.0f);

    float width = (float)Window::get()->getWidth();
    float height = (float)Window::get()->getHeight();

    // Ray calculation is based on Johns Hopkins presentation:
    // http://www.cs.jhu.edu/~cohen/RendTech99/Lectures/Ray_Casting.bw.pdf
    glm::vec3 h0 = look - up * glm::tan(fov); // min height vector
    glm::vec3 h1 = look + up * glm::tan(fov); // max height vector
    metaData.stepH = (h1 - h0) / height;
    h0 += metaData.stepH / 2.0f;

    glm::vec3 w0 = look - right * glm::tan(fov) * width / height; // min width vector
    glm::vec3 w1 = look + right * glm::tan(fov) * width / height; // max width vector
    metaData.stepW = (w1 - w0) / width;
    w0 += metaData.stepW / 2.0f;

    metaData.startCorner = w0 + h0;

    renderLayerOctree->writeMeta(0, &metaData, sizeof(RenderLayerOctree::MetaData));
}

RenderLayer* SceneRenderer::getRenderLayer() const {
    return renderLayerOctree;
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
