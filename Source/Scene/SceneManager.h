#pragma once
#include "Core/Singleton.h"
#include <vector>

class Scene;

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
};
