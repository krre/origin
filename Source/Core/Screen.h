#pragma once
#include "Common.h"
#include <vector>

class Scene;

class Screen {

public:
    Screen();
    virtual void hide();
    virtual void pause();
    virtual void resume();
    virtual void show();

    void update(float dt);
    void render(float dt);
    void resize(uint32_t width, uint32_t height);

    void pushScene(const std::shared_ptr<Scene>& scene);
    void popScene();
    Scene* getCurrentScene() const { return currentScene; }

private:
    std::vector<std::shared_ptr<Scene>> scenes;
    Scene* currentScene = nullptr;
};
