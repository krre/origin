#pragma once
#include "Core/Singleton.h"
#include "Scene.h"
#include <vector>

class RenderManager;

class SceneManager : public Singleton<SceneManager> {

public:
    SceneManager();
    void pushScene(const std::shared_ptr<Scene>& scene);
    void popScene();
    void setScene(const std::shared_ptr<Scene>& scene);

    void update(float dt);
    void draw(float dt);

    void rebuild();

private:
    std::vector<std::shared_ptr<Scene>> scenes;
    std::unique_ptr<RenderManager> renderManager;
};
