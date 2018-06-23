#pragma once
#include "Renderer.h"
#include "ECS/Scenes/Scene.h"
#include "Octree/Octree.h"

namespace Origin {

class RenderPassOctree;

class SceneRenderer : public Renderer {

public:
    SceneRenderer(Object* parent = nullptr);
    ~SceneRenderer();

    static SceneRenderer* get();

    void draw() override;
    RenderPassResource* getRenderPass() const override;

    void addScene(Scene* scene);

private:
    std::vector<Scene*> scenes;
    RenderPassOctree* renderPassOctree;
};

} // Origin
