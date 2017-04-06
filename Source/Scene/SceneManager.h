#pragma once
#include "../Core/Singleton.h"
#include "Scene.h"
#include <vector>

class SceneManager : public Singleton<SceneManager> {

public:
    SceneManager();
    void pushScene(std::shared_ptr<Scene> scene);
    void popScene();
    void setScene(std::shared_ptr<Scene> scene);

    void update(float dt);
    void draw(float dt);

    void rebuild();

    void updateSemaphores();

private:
    std::vector<std::shared_ptr<Scene>> scenes;
};
