#pragma once
#include "../Mesh.h"

class Cube : public Mesh {

public:
    Cube(float width = 1.0, float height = 1.0, float depth = 1.0);

private:
    float width;
    float height;
    float depth;
};
