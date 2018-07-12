#include "SceneRenderer.h"
#include "ECS/Scenes/Scene.h"
#include "Octree/Octree.h"
#include "Debug/DebugEnvironment.h"
#include "Graphics/Render/PolygonalOctreeRenderer.h"
#include "Graphics/Render/RaycastOctreeRenderer.h"

namespace Origin {

static SceneRenderer* instance = nullptr;

SceneRenderer::SceneRenderer(Object* parent) : Origin::Renderer(parent) {
    instance = this;

    if (DebugEnvironment::getEnable() && DebugEnvironment::getSettings()["general"]["renderer"] == static_cast<int>(OctreeRenderer::Type::Raycast)) {
        octreeRenderer = new RaycastOctreeRenderer(this);
    } else {
        octreeRenderer = new PolygonalOctreeRenderer(this);
    }

    Octree* octree = new Octree(Substance(), this);
}

SceneRenderer::~SceneRenderer() {

}

void SceneRenderer::writeCommandBuffer(Vulkan::CommandBuffer* commandBuffer, Vulkan::Framebuffer* framebuffer) {
    octreeRenderer->writeCommandBuffer(commandBuffer, framebuffer);
}

SceneRenderer* SceneRenderer::get() {
    return instance;
}

void SceneRenderer::draw() {
    for (View3D* view : views) {

    }
    octreeRenderer->draw();
}

bool SceneRenderer::getActive() const {
    return views.size() > 0;
}

void SceneRenderer::addView(View3D* view) {
    views.push_back(view);
}

void SceneRenderer::clearViews() {
    views.clear();
}

} // Origin
