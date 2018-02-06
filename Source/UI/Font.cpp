#include "Font.h"
#include "Resource/ResourceManager.h"
#include "VulkanRenderer/Texture.h"
#include "Core/Utils.h"
#include "Core/Application.h"
#include <cmath>
#include <lodepng/lodepng.h>
#include <experimental/filesystem>
#include <vector>

namespace Origin {

Font::Font() {

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

    // Creating atlas based on code https://gist.github.com/baines/b0f9e4be04ba4e6f56cab82eef5008ff

    // Max texture size
    int maxDim = (1 + (face->size->metrics.height >> 6)) * std::ceil(std::sqrt(NUM_GLYPHS));
    int texWidth = 1;

    while (texWidth < maxDim) {
        texWidth <<= 1;
    }

    int texHeight = texWidth;

    // Render glyphs to atlas
    std::vector<unsigned char> pixels(texWidth * texHeight);
    int penX = 0, penY = 0;

    for (int i = 0; i < NUM_GLYPHS; ++i) {
        FT_Load_Char(face, i, FT_LOAD_RENDER | FT_LOAD_FORCE_AUTOHINT | FT_LOAD_TARGET_LIGHT);
        FT_Bitmap* bmp = &face->glyph->bitmap;

        if (penX + bmp->width >= texWidth) {
            penX = 0;
            penY += ((face->size->metrics.height >> 6) + 1);
        }

        for (int row = 0; row < bmp->rows; ++row) {
            for (int col = 0; col < bmp->width; ++col) {
                int x = penX + col;
                int y = penY + row;
                pixels[y * texWidth + x] = bmp->buffer[row * bmp->pitch + col];
            }
        }

        // This is stuff you'd need when rendering individual glyphs out of the atlas
        glyphInfo[i].x0 = penX;
        glyphInfo[i].y0 = penY;
        glyphInfo[i].x1 = penX + bmp->width;
        glyphInfo[i].y1 = penY + bmp->rows;

        glyphInfo[i].offsetX   = face->glyph->bitmap_left;
        glyphInfo[i].offsetY   = face->glyph->bitmap_top;
        glyphInfo[i].advance = face->glyph->advance.x >> 6;

        penX += bmp->width + 1;
    }

    uint32_t size = texWidth * texHeight * 4;
    std::vector<unsigned char> atlasData(size);
    for(int i = 0; i < (texWidth * texHeight); ++i){
        atlasData[i * 4 + 0] |= pixels[i];
        atlasData[i * 4 + 1] |= pixels[i];
        atlasData[i * 4 + 2] |= pixels[i];
        atlasData[i * 4 + 3] |= pixels[i];
    }

    texture = std::make_unique<Vulkan::Texture>(texWidth, texHeight, atlasData.data(), size);

    // Write PNG for testing image
#if 0
    std::string directoryPath = Application::getCurrentDirectory() + Utils::getPathSeparator() + "Cache";

    namespace fs = std::experimental::filesystem;
    if (!fs::exists(directoryPath)) {
        fs::create_directory(directoryPath);
    }

    std::string atlasPath = directoryPath + Utils::getPathSeparator() + "atlas.png";

    lodepng::encode(atlasPath, atlasData.data(), texWidth, texHeight);
#endif
}

} // Origin
