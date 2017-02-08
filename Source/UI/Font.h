#pragma once
#include "../Resource/Resource.h"
#include <map>
#include <glm/glm.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H

class Font : public Resource {

public:
    struct Glyph {
//        GLuint textureId;   // ID handle of the glyph texture
        glm::ivec2 size;    // Size of glyph
        glm::ivec2 bearing;  // Offset from baseline to left/top of glyph
        uint32_t advance;    // Horizontal offset to advance to next glyph
    };

    Font();
    ~Font();
    void setSize(int size);
    int getSize() const { return size; }
    void load(const std::string& path) override;
    Glyph getGlyph(char character) { return characters[character]; }

private:
    int size = 14;
    std::map<char, Glyph> characters;
    FT_Face face;
};
