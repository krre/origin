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

    vertex.pos = { x, height + y}; // Top-Left
    vertices->push_back(vertex);

    vertex.pos = { x, y }; // Bottom-Left
    vertices->push_back(vertex);

    vertex.pos = { width + x, height + y};
    vertices->push_back(vertex); // Top-Right

    vertex.pos = { width + x, height + y }; // Bottom-Left
    vertices->push_back(vertex);

    vertex.pos = { x, y }; // Bottom-Right
    vertices->push_back(vertex);

    vertex.pos = { width + x, y }; // Top-Right
    vertices->push_back(vertex);

    vertextEnd = vertices->size();
}

void UIBatch::addText(float x, float y, const std::string& text, Font* font) {

}

} // Origin
