#pragma once
#include "Drawable.h"
#include "../UI/Control.h"
#include <vector>

class Scene2D : public Drawable {

public:
    Scene2D() {}
    void draw(float dt) override;

private:
    std::vector<std::shared_ptr<Control>> controls;
};
