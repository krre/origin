#pragma once
#include "Scene.h"

class Scene3D : public Scene {

public:
    Scene3D();
    void draw(float dt) override;

private:
    void onWindowResize(int width, int height) override;
};
