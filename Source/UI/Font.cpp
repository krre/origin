#include "Font.h"
#include "Resource/ResourceManager.h"
#include "VulkanRenderer/Texture.h"

namespace Origin {

Font::Font() {

}

Font::~Font() {
    FT_Done_Face(face);
}

void Font::setSize(int size) {
    this->size = size;
}

void Font::load(const std::string& filePath) {
    if (FT_New_Face(ResourceManager::get()->getFreeTypeHandle(), filePath.c_str(), 0, &face)) {
        throw std::runtime_error(std::string("Could not open font ") + filePath);
    }

    setSize(14);
}

} // Origin
