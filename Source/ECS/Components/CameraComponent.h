#pragma once
#include "../Component.h"
#include "../Graphics/Camera.h"

class CameraComponent : public Component {

public:
    CameraComponent();
    shared_ptr<Camera> camera;
};
