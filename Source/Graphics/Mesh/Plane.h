#pragma once
#include "../Mesh.h"

class Plane : public Mesh {

public:
    Plane(int width, int height);

private:
    int width;
    int height;
};
