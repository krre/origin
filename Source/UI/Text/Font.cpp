// Base on article https://en.wikibooks.org/wiki/OpenGL_Programming/Modern_OpenGL_Tutorial_Text_Rendering_02
#include "Font.h"
#include "../../Resource/ResourceManager.h"
#include <algorithm>
#include <fstream>

Font::Font() {

}

Font::~Font() {

}

void Font::setSize(int size) {
    this->size = size;
}

void Font::load(const std::string& path) {
    PRINT(path)

    std::filebuf fileBuffer;
    fileBuffer.open(path, std::ios::in);
    std::istream istream(&fileBuffer);

    assert(istream.good());

    while (!istream.eof()) {
        std::string line;
        std::getline(istream, line);
        PRINT(line)
//        lineStream << line;
//        std::stringstream lineStream;
//        std::string info;
//        lineStream >> info;
//        PRINT(info)
    }
}

int Font::renderText(Vulkan::Buffer* buffer, const std::string& text, float x, float y, float sx, float sy) {


    return 0;
}

void Font::uploadTexture(Vulkan::DeviceMemory* memory) {

}
