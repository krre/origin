#include "SceneRenderer.h"
#include "Vulkan/GpuBuffer.h"
#include "Resource/RenderPass/RenderPassVoxel.h"
#include "Graphics/Render/RenderManager.h"
#include "Base/Window.h"
#include "Base/Game.h"
#include "Octree/Octree.h"
#include <glm/gtc/matrix_transform.hpp>

namespace Origin {

SceneRenderer::SceneRenderer(Object* parent) : Object(parent) {
    renderPassVoxel = new RenderPassVoxel(Game::getRenderManager()->getGraphicsDevice(), this);
    Octree* octree = new Octree(Substance(), this);

    for (const auto& vertex : octree->getVertices()) {
        vertices.push_back(vertex);
    }
}

SceneRenderer::~SceneRenderer() {

}

void SceneRenderer::addScene(Scene* scene) {
    scenes.push_back(scene);
}

void SceneRenderer::drawScenes() {
    for (Scene* scene : scenes) {


    }

    glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)Game::getWindow()->getWidth() / Game::getWindow()->getHeight(), 0.1f, 100.0f);
    glm::mat4 view = glm::lookAt(glm::vec3(0, 0, 5), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    glm::mat4 model = glm::mat4(1.0f);
    float rot = 0;
    model = glm::rotate(model, rot, glm::vec3(0.0, 1.0, 0.0)) * glm::rotate(model, rot, glm::vec3(1.0, 1.0, 1.0));

    glm::mat4 mvp = proj * view * model;

    renderPassVoxel->updateMvp(mvp);
    renderPassVoxel->setVertexCount(vertices.size());

    uint32_t size = vertices.size() * sizeof(Octree::Vertex);
    if (size) {
        renderPassVoxel->getVertexBuffer()->write(vertices.data(), size);
    }

    scenes.clear();
}

} // Origin
