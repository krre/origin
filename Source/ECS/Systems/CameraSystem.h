#pragma once
#include "../System.h"

class CameraSystem : public System {

public:
    CameraSystem();
    void process(float dt) override;
};
