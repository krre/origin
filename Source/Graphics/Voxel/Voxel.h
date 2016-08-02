#pragma once
#include "../../Core/Object.h"
#include <glm/glm.hpp>

class Voxel : public Object {

public:
    Voxel();
    glm::vec3 color;
};
