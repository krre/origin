#pragma once
#include "Scene.h"

class Scene3D : public Scene {

public:
    Scene3D();

private:
    void onWindowResize(int width, int height) override;
};
