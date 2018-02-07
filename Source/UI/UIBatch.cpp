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

        // New line
        if (sign == '\n') {
            posX = x;
            int lineHeight = font->getSize() + font->getSize() * 0.2; // TODO: Take from Label
            posY += lineHeight;
            continue;
        }

        Vertex vertex = {};
        vertex.color = color.getRgba();

        vertex.pos = { posX + glyphInfo.offsetX, posY - glyphInfo.offsetY }; // Top-Left
        vertex.uv = { glyphInfo.u0, glyphInfo.v0 };
        vertices->push_back(vertex);

        vertex.pos = { posX + glyphInfo.width + glyphInfo.offsetX, posY - glyphInfo.offsetY }; // Top-Right
        vertex.uv = { glyphInfo.u1, glyphInfo.v0 };
        vertices->push_back(vertex);

        vertex.pos = { posX + glyphInfo.offsetX, posY + glyphInfo.height - glyphInfo.offsetY }; // Bottom-Left
        vertex.uv = { glyphInfo.u0, glyphInfo.v1 };
        vertices->push_back(vertex);

        vertex.pos = { posX + glyphInfo.offsetX, posY + glyphInfo.height - glyphInfo.offsetY }; // Bottom-Left
        vertex.uv = { glyphInfo.u0, glyphInfo.v1 };
        vertices->push_back(vertex);

        vertex.pos = { posX + glyphInfo.offsetX + glyphInfo.width, posY - glyphInfo.offsetY }; // Top-Right
        vertex.uv = { glyphInfo.u1, glyphInfo.v0 };
        vertices->push_back(vertex);

        vertex.pos = { posX + glyphInfo.offsetX + glyphInfo.width, posY + glyphInfo.height - glyphInfo.offsetY }; // Bottom-Right
        vertex.uv = { glyphInfo.u1, glyphInfo.v1 };
        vertices->push_back(vertex);

        vertextEnd = vertices->size();

        posX += glyphInfo.advanceX;
    }
}

} // Origin
