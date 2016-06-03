#pragma once
#include "../Core/Object.h"
#include "Scene.h"
#include "../Graphics/Camera.h"

class Viewport : public Object {

public:
    Viewport();

    void setScene(Scene* const scene) { this->scene = scene; }
    Scene* getScene() const { return scene; }

private:
    Scene* scene;
    shared_ptr<Camera> camera;
};
