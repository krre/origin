#pragma once
#include "../Core/Object.h"
#include "Scene.h"
#include "../Graphics/Camera.h"

class Viewport : public Object {

public:
    Viewport();

    void setScene(shared_ptr<Scene> const scene) { this->scene = scene; }
    shared_ptr<Scene> getScene() const { return scene; }

private:
    shared_ptr<Scene> scene;
    shared_ptr<Camera> camera;
};
