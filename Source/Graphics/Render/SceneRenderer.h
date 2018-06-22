#pragma once
#include "Core/Object.h"
#include "ECS/Scenes/Scene.h"
#include "Octree/Octree.h"

namespace Origin {

class RenderPassOctree;

class SceneRenderer : public Object {

public:
    SceneRenderer(Object* parent = nullptr);
    ~SceneRenderer();

    void addScene(Scene* scene);
    void drawScenes();
    RenderPassOctree* getRenderPassOctree() const { return renderPassOctree; }

private:
    std::vector<Scene*> scenes;
    RenderPassOctree* renderPassOctree;
};

} // Origin
