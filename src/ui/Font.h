#pragma once
#include "resource/Resource.h"

#undef HAVE_STDINT_H
#include <ft2build.h>
#include FT_FREETYPE_H

namespace Vulkan {
    class Texture;
}

const uint32_t GLYPHS_COUNT = 128;

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
    int size() const { return m_size; }

    void load(const std::string& filePath) override;
    Vulkan::Texture* texture() const { return m_texture.get(); }
    GlyphInfo& gliphInfo(int codechar);
    int lineHeight() const { return m_lineHeight; }
    int ascender() const { return m_ascender; }
    int descender() const { return m_descender; }

private:
    FT_Face m_face;
    int m_size = 14;
    std::vector<GlyphInfo> m_glyphInfos;
    std::unique_ptr<Vulkan::Texture> m_texture;
    int m_lineHeight;
    int m_ascender;
    int m_descender;
};
