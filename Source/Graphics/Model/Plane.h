#pragma once
#include "../../SceneGraph/Node.h"

class Plane : public Node {

public:
    Plane();
    void draw() override;
};
