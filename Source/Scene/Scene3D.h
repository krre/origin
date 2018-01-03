#pragma once
#include "Scene.h"

namespace Origin {

class Scene3D : public Scene {

public:
    Scene3D();

private:
    void onWindowResize(int width, int height) override;
};

} // Origin
