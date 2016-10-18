#pragma once
#include "../System.h"

class PhisicsSystem : public System {

public:
    PhisicsSystem();
    void process(float dt) override;
};
