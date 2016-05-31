#pragma once
#include "View.h"
#include "../Graphics3D/Camera.h"
#include "../Graphics3D/Scene.h"
#include <memory>

class PlayerView : public View {

public:
    PlayerView();

private:
    std::shared_ptr<Camera> camera;
    std::shared_ptr<Scene> scene;
};
