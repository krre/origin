#pragma once
#include "Resource/Resource.h"
#include <map>

#undef HAVE_STDINT_H
#include <ft2build.h>
#include FT_FREETYPE_H

namespace Vulkan {
    class Texture;
}

namespace Origin {

const uint32_t NUM_GLYPHS = 128;

class Font : public Resource {

public:

    // Glyph metrics:
    // --------------
    //
    //                       xmin                     xmax
    //                        |                         |
    //                        |<-------- width -------->|
    //                        |                         |
    //              |         +-------------------------+----------------- ymax
    //              |         |    ggggggggg   ggggg    |     ^        ^
    //              |         |   g:::::::::ggg::::g    |     |        |
    //              |         |  g:::::::::::::::::g    |     |        |
    //              |         | g::::::ggggg::::::gg    |     |        |
    //              |         | g:::::g     g:::::g     |     |        |
    //    offsetX  -|-------->| g:::::g     g:::::g     |  offsetY     |
    //              |         | g:::::g     g:::::g     |     |        |
    //              |         | g::::::g    g:::::g     |     |        |
    //              |         | g:::::::ggggg:::::g     |     |        |
    //              |         |  g::::::::::::::::g     |     |      height
    //              |         |   gg::::::::::::::g     |     |        |
    //  baseline ---*---------|---- gggggggg::::::g-----*--------      |
    //            / |         |             g:::::g     |              |
    //     origin   |         | gggggg      g:::::g     |              |
    //              |         | g:::::gg   gg:::::g     |              |
    //              |         |  g::::::ggg:::::::g     |              |
    //              |         |   gg:::::::::::::g      |              |
    //              |         |     ggg::::::ggg        |              |
    //              |         |         gggggg          |              v
    //              |         +-------------------------+----------------- ymin
    //              |                                   |
    //              |------------- advanceX ----------->|

    struct GlyphInfo {
        float u0, v0, u1, v1;
        int offsetX, offsetY;
        int width, height;
        int advanceX;
    };

    Font();
    ~Font();
    void setSize(int size);
    int getSize() const { return size; }
    void load(const std::string& filePath) override;
    Vulkan::Texture* getTexture() const { return texture.get(); }
    GlyphInfo& getGliphInfo(int codechar) { return glyphInfos.at(codechar); }
    int getLineHeight() const { return lineHeight; }
    int getAscender() const { return ascender; }
    int getDescender() const { return descender; }

private:
    FT_Face face;
    int size = 14;
    std::vector<GlyphInfo> glyphInfos;
    std::unique_ptr<Vulkan::Texture> texture;
    int lineHeight;
    int ascender;
    int descender;
};

} // Origin
