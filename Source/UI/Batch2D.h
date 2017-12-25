#pragma once
#include "UITypes.h"
#include <vector>
#include <glm/glm.hpp>

class Batch2D {

public:

    struct Vertex {
        glm::vec2 pos;
        glm::vec2 uv;
        uint16_t color;
    };

    Batch2D();
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;
    ControlType controlType = ControlType::USUAL;

private:

};
