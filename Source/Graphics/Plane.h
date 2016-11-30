#pragma once
#include "Mesh.h"

class Plane : public Mesh {

public:
    Plane(float width = 1.0, float height = 1.0);

private:
    float width;
    float height;
};
