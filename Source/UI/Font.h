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

class Font : public Resource {

public:

    struct Character {
        int x;
        int y;
        int width;
        int height;
        int xoffset;
        int yoffset;
        int xadvance;
    } character;

    Font();
    ~Font();
    void setSize(int size);
    int getSize() const { return size; }
    void load(const std::string& filePath) override;
    Vulkan::Texture* getTexture() const { return texture.get(); }

private:
    FT_Face face;
    int size = 14;
    std::map<int, Character> characters;
    std::unique_ptr<Vulkan::Texture> texture;
};

} // Origin
