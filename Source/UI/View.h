#pragma once
#include "Control.h"

class Scene;

class View : public Control {

public:
    View();
    ~View();
    void update(float dt);
    void draw(float dt);
    void render(float dt);
    Scene* getScene() const { return scene.get(); }
    void resize(uint32_t width, uint32_t height);

private:
    std::shared_ptr<Scene> scene;
};
