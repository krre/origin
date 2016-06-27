#pragma once
#include "../System.h"

class TransformSystem : public System {

public:
    TransformSystem();
    void process(float dt) override;
};
