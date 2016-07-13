#pragma once
#include "Drawable.h"

class Model : public Drawable {

public:
    Model();
    void draw(float dt) override;
};
