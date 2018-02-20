#pragma once
#include "Core/Object.h"

namespace Origin {

class Scene;

class SceneRenderer : public Object {

public:
    SceneRenderer(Object* parent = nullptr);
    ~SceneRenderer();

    void addScene(Scene* scene);
    void drawScenes();

private:
    std::vector<Scene*> scenes;
};

} // Origin
