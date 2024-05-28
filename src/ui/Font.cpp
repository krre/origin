#include "Font.h"
#include "resource/ResourceManager.h"
#include "vulkan/Texture.h"
#include "graphics/render/RenderManager.h"
#include <cmath>
#include <lodepng/lodepng.h>
#include <vector>
#include <filesystem>


Font::Font() {
    glyphInfos.resize(GLYPHS_COUNT);
}

Font::~Font() {
    FT_Done_Face(face);
}

void Font::setSize(int size) {
    this->size = size;
    FT_Set_Pixel_Sizes(face, 0, size);
}

void Font::load(const std::string& filePath) {
    if (FT_New_Face(ResourceManager::get()->getFreeTypeHandle(), filePath.c_str(), 0, &face)) {
        throw std::runtime_error(std::string("Could not open font ") + filePath);
    }

    setSize(14);

    lineHeight = face->size->metrics.height >> 6;
    ascender = face->size->metrics.ascender >> 6;
    descender = face->size->metrics.descender >> 6;

    // Creating atlas based on code https://gist.github.com/baines/b0f9e4be04ba4e6f56cab82eef5008ff

    // Max texture size
    int maxDim = (1 + lineHeight) * std::ceil(std::sqrt(GLYPHS_COUNT));
    int texWidth = 1;

    while (texWidth < maxDim) {
        texWidth <<= 1;
    }

    int texHeight = texWidth;

    // Render glyphs to atlas
    std::vector<unsigned char> pixels(texWidth * texHeight);
    int penX = 0, penY = 0;

    for (int i = 0; i < GLYPHS_COUNT; ++i) {
        FT_Load_Char(face, i, FT_LOAD_RENDER | FT_LOAD_FORCE_AUTOHINT | FT_LOAD_TARGET_LIGHT);
        FT_Bitmap* bitmap = &face->glyph->bitmap;

        if (penX + bitmap->width >= texWidth) {
            penX = 0;
            penY += ((face->size->metrics.height >> 6) + 1);
        }

        for (int row = 0; row < bitmap->rows; ++row) {
            for (int col = 0; col < bitmap->width; ++col) {
                int x = penX + col;
                int y = penY + row;
                pixels[y * texWidth + x] = bitmap->buffer[row * bitmap->pitch + col];
            }
        }

        GlyphInfo* glyphInfo = &glyphInfos[i];

        glyphInfo->offsetX = face->glyph->bitmap_left;
        glyphInfo->offsetY = face->glyph->bitmap_top;
        glyphInfo->width = bitmap->width;
        glyphInfo->height = bitmap->rows;
        glyphInfo->advanceX = face->glyph->advance.x >> 6;

        glyphInfo->u0 = penX / (float)texWidth;
        glyphInfo->v0 = penY / (float)texHeight;
        glyphInfo->u1 = (penX + glyphInfo->width) / (float)texWidth;
        glyphInfo->v1 = (penY + glyphInfo->height) / (float)texHeight;

        penX += bitmap->width + 1;
    }

    uint32_t size = texWidth * texHeight * 4;
    std::vector<unsigned char> atlasData(size);

    for (int i = 0; i < (texWidth * texHeight); ++i) {
        atlasData[i * 4 + 0] = 0xff; // R
        atlasData[i * 4 + 1] = 0xff; // G
        atlasData[i * 4 + 2] = 0xff; // B
        atlasData[i * 4 + 3] = pixels[i]; // A
    }

    atlasData[3] = 0xff; // Alpha dot for shapes
    glyphInfos.at(0).u1 = 1.0f / texWidth;
    glyphInfos.at(0).v1 = 1.0f / texHeight;

    texture = std::make_unique<Vulkan::Texture>(RenderManager::get()->getGraphicsDevice(), texWidth, texHeight, atlasData.data(), size);

    // Write PNG for testing image
#if 0
    std::string directoryPath = Game::getCurrentDirectory() + Utils::getPathSeparator() + "Cache";

    if (!std::filesystem::exists(directoryPath)) {
        std::filesystem::create_directory(directoryPath);
    }

    std::string atlasPath = directoryPath + Utils::getPathSeparator() + "atlas.png";

    lodepng::encode(atlasPath, atlasData.data(), texWidth, texHeight);
#endif
}

Font::GlyphInfo&Font::getGliphInfo(int codechar) {
    char questionMark = '?';
    return glyphInfos.at(codechar <= GLYPHS_COUNT ? codechar : (int)questionMark);
}
