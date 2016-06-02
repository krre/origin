#pragma once
#include "../Core/Object.h"
#include "Scene.h"

class Viewport : public Object {

public:
    Viewport();

    void setScene(Scene* const scene) { this->scene = scene; }
    Scene* getScene() { return scene; }

private:
    Scene* scene;
};
