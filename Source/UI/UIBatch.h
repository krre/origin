#pragma once
#include <vector>
#include <glm/glm.hpp>
#include "Graphics/Color.h"

namespace Origin {

class Texture;

class UIBatch {

public:

    struct Vertex {
        glm::vec2 pos;
        glm::vec2 ui;
        uint32_t color;
    };

    UIBatch(std::vector<Vertex>* vertices);
    Color color;
    Texture* texture = nullptr;
    std::vector<Vertex>* vertices = nullptr;
    uint32_t vertexStart = 0;
    uint32_t vertextEnd = 0;

    void addQuad(float x, float y, float width, float height);
};

} // Origin
