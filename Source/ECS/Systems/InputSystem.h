#pragma once
#include "../System.h"

class InputSystem : public System {

public:
    InputSystem();
    void process(float dt) override;
};
