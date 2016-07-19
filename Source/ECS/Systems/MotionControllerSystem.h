#pragma once
#include "../System.h"

class MotionControllerSystem : public System {

public:
    MotionControllerSystem();
    void process(float dt) override;

private:
};
