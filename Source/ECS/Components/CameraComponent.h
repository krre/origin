#pragma once
#include "../Component.h"
#include "../Graphics/Camera.h"

class CameraComponent : public Component {

public:
    CameraComponent() { type = Component::Type::Camera; }
    std::shared_ptr<Camera> camera;
};
