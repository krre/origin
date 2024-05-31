#include "SceneRenderer.h"
#include "debug/DebugEnvironment.h"
#include "graphics/render/PolygonalOctreeRenderer.h"
#include "graphics/render/RaycastOctreeRenderer.h"
#include "graphics/render/View3DBatch.h"
#include <octree/Octree.h>

static SceneRenderer* instance = nullptr;

SceneRenderer::SceneRenderer(Object* parent) : Renderer(parent) {
    instance = this;

    if (DebugEnvironment::enable() && DebugEnvironment::settings()["general"]["renderer"] == static_cast<int>(OctreeRenderer::Type::Raycast)) {
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

bool SceneRenderer::active() const {
    return views.size() > 0;
}

void SceneRenderer::addView(View3D* view) {
    views.push_back(view);
}

void SceneRenderer::clearViews() {
    views.clear();
}
