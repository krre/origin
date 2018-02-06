#include "UIBatch.h"
#include "Font.h"

namespace Origin {

UIBatch::UIBatch(std::vector<Vertex>* vertices) :
        vertices(vertices) {
    vertexStart = vertices->size();
    vertextEnd = vertices->size();
}

void UIBatch::addQuad(float x, float y, float width, float height, Font* font) {
    Font::GlyphInfo& glyphInfo = font->getGliphInfo(0);
    Vertex vertex = {};
    vertex.color = color.getRgba();

    vertex.pos = { x, y }; // Top-Left
    vertex.uv = { glyphInfo.u0, glyphInfo.v0 };
    vertices->push_back(vertex);

    vertex.pos = { x + width, y }; // Top-Right
    vertex.uv = { glyphInfo.u1, glyphInfo.v0 };
    vertices->push_back(vertex);

    vertex.pos = { x, y + height }; // Bottom-Left
    vertex.uv = { glyphInfo.u0, glyphInfo.v1 };
    vertices->push_back(vertex);

    vertex.pos = { x, y + height }; // Bottom-Left
    vertex.uv = { glyphInfo.u0, glyphInfo.v1 };
    vertices->push_back(vertex);

    vertex.pos = { x + width, y }; // Top-Right
    vertex.uv = { glyphInfo.u1, glyphInfo.v0 };
    vertices->push_back(vertex);

    vertex.pos = { x + width, y + height }; // Bottom-Right
    vertex.uv = { glyphInfo.u1, glyphInfo.v1 };
    vertices->push_back(vertex);

    vertextEnd = vertices->size();
}

void UIBatch::addText(float x, float y, const std::string& text, Font* font) {
    int posX = x;
    int posY = y;

    for (auto& sign : text) {
        Font::GlyphInfo& glyphInfo = font->getGliphInfo((int)sign);

        Vertex vertex = {};
        vertex.color = color.getRgba();

        vertex.pos = { posX, posY }; // Top-Left
        vertex.uv = { glyphInfo.u0, glyphInfo.v0 };
        vertices->push_back(vertex);

        vertex.pos = { posX + glyphInfo.width, posY }; // Top-Right
        vertex.uv = { glyphInfo.u1, glyphInfo.v0 };
        vertices->push_back(vertex);

        vertex.pos = { posX, posY + glyphInfo.height }; // Bottom-Left
        vertex.uv = { glyphInfo.u0, glyphInfo.v1 };
        vertices->push_back(vertex);

        vertex.pos = { posX, posY + glyphInfo.height }; // Bottom-Left
        vertex.uv = { glyphInfo.u0, glyphInfo.v1 };
        vertices->push_back(vertex);

        vertex.pos = { posX + glyphInfo.width, posY }; // Top-Right
        vertex.uv = { glyphInfo.u1, glyphInfo.v0 };
        vertices->push_back(vertex);

        vertex.pos = { posX + glyphInfo.width, posY + glyphInfo.height }; // Bottom-Right
        vertex.uv = { glyphInfo.u1, glyphInfo.v1 };
        vertices->push_back(vertex);

        vertextEnd = vertices->size();

        posX += glyphInfo.advanceX + glyphInfo.offsetX;
    }
}

} // Origin
