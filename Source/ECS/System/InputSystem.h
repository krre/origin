#pragma once
#include "../System.h"

class InputSystem : public System {

public:
    InputSystem();
    void update(float dt) override;
};
