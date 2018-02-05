#pragma once
#include "Resource/Resource.h"
#include <map>

#undef HAVE_STDINT_H
#include <ft2build.h>
#include FT_FREETYPE_H

#define NUM_GLYPHS 128

namespace Vulkan {
    class Texture;
}

namespace Origin {

class Font : public Resource {

public:

    struct GlyphInfo {
        int x0, y0, x1, y1;	// coords of glyph in the texture atlas
        int offsetX, offsetY; // left & top bearing when rendering
        int advance; // x advance when rendering
    } glyphInfo [NUM_GLYPHS];

    Font();
    ~Font();
    void setSize(int size);
    int getSize() const { return size; }
    void load(const std::string& filePath) override;
    Vulkan::Texture* getTexture() const { return texture.get(); }

private:
    FT_Face face;
    int size = 14;
    std::unique_ptr<Vulkan::Texture> texture;
};

} // Origin
