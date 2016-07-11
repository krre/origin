#pragma once
#include "../Component.h"
#include "../Graphics/Camera.h"

class CameraComponent : public Component {

public:
    CameraComponent();
    std::shared_ptr<Camera> camera;
};
