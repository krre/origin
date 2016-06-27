#pragma once
#include "../System.h"

class RenderSystem : public System {

public:
    RenderSystem();
    void process(float dt) override;
};
