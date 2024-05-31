#include "UIBatch.h"
#include "Font.h"

UIBatch::UIBatch(std::vector<Vertex>* vertices) :
        vertices(vertices) {
    vertexStart = vertices->size();
    vertextEnd = vertices->size();
}

void UIBatch::addQuad(float x, float y, float width, float height, Font* font) {
    Font::GlyphInfo& glyphInfo = font->gliphInfo(0);
    Vertex vertex = {};
    vertex.color = color.rgba();

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
    int lineHeight = font->lineHeight();

    // Find highest sign for first row
    int maxHeigth = 0;
    for (auto& sign : text) {
        if (sign == '\n') {
            break;
        }

        Font::GlyphInfo& glyphInfo = font->gliphInfo((int)sign);
        maxHeigth = std::max(maxHeigth, glyphInfo.offsetY);
    }

    for (auto& sign : text) {
        Font::GlyphInfo& glyphInfo = font->gliphInfo((int)sign);

        // New line
        if (sign == '\n') {
            posX = x;
            posY += lineHeight;
            continue;
        }

        Vertex vertex = {};
        vertex.color = color.rgba();

        int xo = posX + glyphInfo.offsetX;
        // TODO: maxHeigth need only for first row.
        // May be for other rows use ascender.
        int yo = posY + maxHeigth - glyphInfo.offsetY;

        vertex.pos = { xo, yo }; // Top-Left
        vertex.uv = { glyphInfo.u0, glyphInfo.v0 };
        vertices->push_back(vertex);

        vertex.pos = { xo + glyphInfo.width, yo }; // Top-Right
        vertex.uv = { glyphInfo.u1, glyphInfo.v0 };
        vertices->push_back(vertex);

        vertex.pos = { xo, yo + glyphInfo.height }; // Bottom-Left
        vertex.uv = { glyphInfo.u0, glyphInfo.v1 };
        vertices->push_back(vertex);

        vertex.pos = { xo, yo + glyphInfo.height }; // Bottom-Left
        vertex.uv = { glyphInfo.u0, glyphInfo.v1 };
        vertices->push_back(vertex);

        vertex.pos = { xo + glyphInfo.width, yo }; // Top-Right
        vertex.uv = { glyphInfo.u1, glyphInfo.v0 };
        vertices->push_back(vertex);

        vertex.pos = { xo + glyphInfo.width, yo + glyphInfo.height }; // Bottom-Right
        vertex.uv = { glyphInfo.u1, glyphInfo.v1 };
        vertices->push_back(vertex);

        vertextEnd = vertices->size();

        posX += glyphInfo.advanceX;
    }
}
