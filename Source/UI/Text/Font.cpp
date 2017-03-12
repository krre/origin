// Base on article https://en.wikibooks.org/wiki/OpenGL_Programming/Modern_OpenGL_Tutorial_Text_Rendering_02
#include "Font.h"
#include "../../Resource/ResourceManager.h"
#include "../../Core/Utils.h"
#include <fstream>

Font::Font() {

}

Font::~Font() {

}

void Font::setSize(int size) {
    this->size = size;
}

void Font::load(const std::string& path) {
    std::filebuf fileBuffer;
    fileBuffer.open(path, std::ios::in);
    std::istream istream(&fileBuffer);

    assert(istream.good());

    // Parse fnt file
    while (!istream.eof()) {
        std::string line;
        std::getline(istream, line);

        std::vector<std::string> words = Utils::split(line, ' ');
        if (!words.size()) {
            continue;
        }

        std::string& head = words.at(0);

        if (head == "common") {
            for (int i = 1; i < words.size(); i++) {
                std::vector<std::string> pair = Utils::split(words.at(i), '=');
                if (pair.at(0) == "scaleW") {
                    atlasSize.x = std::stoi(pair.at(1));
                } else if (pair.at(0) == "scaleH") {
                    atlasSize.y = std::stoi(pair.at(1));
                }
            }
        } else if (head == "char") {
            Character character = {};
            int id;
            for (int i = 1; i < words.size(); i++) {
                std::vector<std::string> pair = Utils::split(words.at(i), '=');
                std::string& name = pair.at(0);
                int value = std::stoi(pair.at(1));
                if (name == "id") {
                    id = value;
                } else if (name == "x") {
                    character.x = value;
                } else if (name == "y") {
                    character.y = value;
                } else if (name == "width") {
                    character.width = value;
                } else if (name == "height") {
                    character.heigth = value;
                } else if (name == "xoffset") {
                    character.xoffset = value;
                } else if (name == "yoffset") {
                    character.yoffset = value;
                } else if (name == "xadvance") {
                    character.xadvance = value;
                }
            }

            characters[id] = character;
        }
    }

    // Load png texture

}

int Font::renderText(Vulkan::Buffer* buffer, const std::string& text, float x, float y, float sx, float sy) {


    return 0;
}

void Font::uploadTexture(Vulkan::DeviceMemory* memory) {

}
