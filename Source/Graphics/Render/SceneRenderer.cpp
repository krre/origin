#include "SceneRenderer.h"
#include "Octree/Octree.h"
#include "Debug/DebugEnvironment.h"
#include "Graphics/Render/PolygonalOctreeRenderer.h"
#include "Graphics/Render/RaycastOctreeRenderer.h"
#include "Graphics/Render/View3DBatch.h"

static SceneRenderer* instance = nullptr;

SceneRenderer::SceneRenderer(Object* parent) : Renderer(parent) {
    instance = this;

    if (DebugEnvironment::getEnable() && DebugEnvironment::getSettings()["general"]["renderer"] == static_cast<int>(OctreeRenderer::Type::Raycast)) {
        octreeRenderer = new RaycastOctreeRenderer(this);
    } else {
        octreeRenderer = new PolygonalOctreeRenderer(this);
    }

    Octree::Octree* octree = new Octree::Octree(Octree::Substance(), this);
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
        octreeRenderer->drawView(view);
    }
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
