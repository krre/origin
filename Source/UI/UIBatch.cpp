#include "UIBatch.h"

namespace Origin {

UIBatch::UIBatch(std::vector<Vertex>* vertices) :
        vertices(vertices) {
    vertexStart = vertices->size();
    vertextEnd = vertices->size();
}

void UIBatch::addQuad(float x, float y, float width, float height) {
    Vertex vertex = {};
    vertex.color = color.getRgba();

    vertex.pos = { x, y }; // Top-Left
    vertices->push_back(vertex);

    vertex.pos = { x, y + height }; // Bottom-Left
    vertices->push_back(vertex);

    vertex.pos = { x + width, y };
    vertices->push_back(vertex); // Top-Right

    vertex.pos = { x, y + height }; // Bottom-Left
    vertices->push_back(vertex);

    vertex.pos = { x + width, y + height }; // Bottom-Right
    vertices->push_back(vertex);

    vertex.pos = { x + width, y }; // Top-Right
    vertices->push_back(vertex);

    vertextEnd = vertices->size();
}

} // Origin
