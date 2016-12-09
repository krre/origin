#pragma once
#include "Scene.h"

class Scene3D : public Scene {

public:
    Scene3D();

private:
    void draw(float dt) override;
    void onWindowResize(int width, int height) override;
};
