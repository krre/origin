#pragma once
#include "Scene3D.h"

class WorldScene : public Scene3D {

public:
    WorldScene();
    void draw(float dt) override;
    void update(float dt) override;
};
