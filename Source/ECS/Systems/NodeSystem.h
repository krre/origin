#pragma once
#include "../System.h"

class NodeSystem : public System {

public:
    NodeSystem();
    void process(float dt) override;
};
