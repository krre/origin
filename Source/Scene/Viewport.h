#pragma once
#include "../Core/Object.h"
#include "../Graphics/Camera.h"
#include "../Scene/Scene.h"

class Viewport : public Object {

public:
    Viewport();
    void update(double dt);
    void render();

    void setScene(shared_ptr<Scene> const scene) { this->scene = scene; }
    shared_ptr<Scene> getScene() const { return scene; }

    shared_ptr<Camera> getCamera() const { return camera; }

private:
    shared_ptr<Scene> scene;
    shared_ptr<Camera> camera;

};
