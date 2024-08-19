#pragma once
#include <vector>
#include <glm/glm.hpp>
#include "graphics/Color.h"

namespace Vulkan {
    class Texture;
}

class Font;

class UIBatch {
public:
    struct Vertex {
        glm::vec2 pos;
        glm::vec2 uv;
        glm::vec4 color;
    };

    UIBatch(std::vector<Vertex>* vertices);
    Color color;
    Vulkan::Texture* texture = nullptr;
    std::vector<Vertex>* vertices = nullptr;
    uint32_t vertexStart = 0;
    uint32_t vertextEnd = 0;

    void addQuad(float x, float y, float width, float height, Font* font);
    void addText(float x, float y, const std::string& text, Font* font);
};
