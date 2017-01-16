#pragma once
#include "../System.h"
#include "../../Graphics/Drawable.h"
#include <vector>

class RenderSystem : public System {

public:
    RenderSystem();
    void process(float dt) override;

private:
    std::vector<Origin::Drawable*> drawables;
};
