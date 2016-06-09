#pragma once
#include "../Core/Object.h"
#include "../Graphics/Camera.h"
#include "../Scene/Scene.h"

class View : public Object {

public:
    View();
    void update(double dt);
    void render();

    void setScene(shared_ptr<Scene> const scene) { this->scene = scene; }
    shared_ptr<Scene> getScene() const { return scene; }

private:
    shared_ptr<Scene> scene;
    shared_ptr<Camera> camera;
};
