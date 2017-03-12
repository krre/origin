// Base on article https://en.wikibooks.org/wiki/OpenGL_Programming/Modern_OpenGL_Tutorial_Text_Rendering_02
#include "Font.h"
#include "../../Resource/ResourceManager.h"
#include <algorithm>

Font::Font() {

}

Font::~Font() {
    FT_Done_Face(face);
}

void Font::setSize(int size) {
    this->size = size;

    FT_Set_Pixel_Sizes(face, 0, size);
    glyph = face->glyph;

    unsigned int w = 0;
    unsigned int h = 0;

    // Load first 128 characters of ASCII set
    for (uint8_t i = 32; i < 128; i++) {
        if (FT_Load_Char(face, i, FT_LOAD_RENDER)) {
            ERROR("Failed to load Glyph: " << i)
            continue;
        }

        w += glyph->bitmap.width;
        h = std::max(h, glyph->bitmap.rows);

        character[i].ax = glyph->advance.x >> 6;
        character[i].ay = glyph->advance.y >> 6;

        character[i].bw = glyph->bitmap.width;
        character[i].bh = glyph->bitmap.rows;

        character[i].bl = glyph->bitmap_left;
        character[i].bt = glyph->bitmap_top;

        character[i].tx = w; // preliminary tx
    }

    for (uint8_t i = 32; i < 128; i++) {
        character[i].tx /= w; // final tx
    }

    atlasWidth = w;
    atlasHeight = h;
}

void Font::load(const std::string& path) {
    if (FT_New_Face(ResourceManager::get()->getFreeTypeHandler(), path.c_str(), 0, &face)) {
        ERROR("Could not open font " << path);
        return;
    }

    setSize(14);
}

int Font::renderText(Vulkan::Buffer* buffer, const std::string& text, float x, float y, float sx, float sy) {
    struct Point {
        float x;
        float y;
        float s;
        float t;
    } coords[6 * text.size()];

    int n = 0;

    for (const char *p = text.c_str(); *p; p++) {
        float x2 = x + character[*p].bl * sx;
        float y2 = -y - character[*p].bt * sy;
        float w = character[*p].bw * sx;
        float h = character[*p].bh * sy;

        // Advance the cursor to the start of the next character
        x += character[*p].ax * sx;
        y += character[*p].ay * sy;

        // Skip glyphs that have no pixels
        if (!w || !h) {
            continue;
        }

        coords[n++] = { x2, -y2, character[*p].tx, 0 };
        coords[n++] = { x2 + w, -y2, character[*p].tx + character[*p].bw / atlasWidth, 0 };
        coords[n++] = { x2, -y2 - h, character[*p].tx, character[*p].bh / atlasHeight }; //remember: each glyph occupies a different amount of vertical space
        coords[n++] = { x2 + w, -y2, character[*p].tx + character[*p].bw / atlasWidth, 0 };
        coords[n++] = { x2, -y2 - h, character[*p].tx, character[*p].bh / atlasHeight };
        coords[n++] = { x2 + w, -y2 - h, character[*p].tx + character[*p].bw / atlasWidth, character[*p].bh / atlasHeight };
    }

    buffer->write(0, sizeof(coords), coords);

//    glBufferData(GL_ARRAY_BUFFER, sizeof coords, coords, GL_DYNAMIC_DRAW);
    //    glDrawArrays(GL_TRIANGLES, 0, n);

    return n;
}

void Font::uploadTexture(Vulkan::DeviceMemory* memory) {
    int offset = 0;
    for (int i = 32; i < 128; i++) {
        if (FT_Load_Char(face, i, FT_LOAD_RENDER)) {
            continue;
        }

        int count = glyph->bitmap.rows * glyph->bitmap.width;
        if (count) {
            void* mapData;
            memory->map(count, offset, &mapData);
            memcpy(mapData, glyph->bitmap.buffer, count);
            memory->unmap();
            offset += count;
        }

//        glTexSubImage2D(GL_TEXTURE_2D, 0, x, 0, g->bitmap.width, g->bitmap.rows, GL_ALPHA, GL_UNSIGNED_BYTE, g->bitmap.buffer);

    }
}
