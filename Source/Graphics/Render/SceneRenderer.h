#pragma once
#include "Core/Object.h"
#include "ECS/Scenes/Scene.h"
#include "Octree/Octree.h"

namespace Origin {

class RenderPassVoxel;

class SceneRenderer : public Object {

public:
    SceneRenderer(Object* parent = nullptr);
    ~SceneRenderer();

    void addScene(Scene* scene);
    void drawScenes();
    std::vector<Octree::Vertex>* getVerticles() { return &vertices; }
    RenderPassVoxel* getRenderPassVoxel() const { return renderPassVoxel; }

private:
    std::vector<Scene*> scenes;
    std::vector<Octree::Vertex> vertices;
    RenderPassVoxel* renderPassVoxel;
};

} // Origin
