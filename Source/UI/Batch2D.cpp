#include "Batch2D.h"

namespace Origin {

Batch2D::Batch2D(std::vector<Vertex>* vertices) :
        vertices(vertices) {
    vertexStart = vertices->size();
    vertextEnd = vertices->size();
}

void Batch2D::addQuad(float x, float y, float width, float height) {
    vertices->resize(vertices->size() + 6 * sizeof(Vertex));
    Vertex vertex = {};
    vertex.color = color.getArgb();

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

    vertextEnd = vertices->size();
}

} // Origin
