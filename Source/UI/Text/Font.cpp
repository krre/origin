// Base on article https://en.wikibooks.org/wiki/OpenGL_Programming/Modern_OpenGL_Tutorial_Text_Rendering_02
#include "Font.h"
#include "../../Resource/ResourceManager.h"
#include "../../Core/Utils.h"
#include <fstream>
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

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

        if (head == "page") {
            // Load png texture
            std::vector<std::string> pair = Utils::split(words.at(2), '=');
            std::string& textureName = pair.at(1);
            const char quote = '\"';
            Utils::removeChar(textureName, quote);
            fs::path fontPath(path);
            std::string texturePath = fontPath.parent_path().string() + Utils::getPathSeparator() + textureName;
            texture = std::make_shared<Texture>(texturePath);
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
                    character.height = value;
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
}

int Font::renderText(Vulkan::Buffer* vertexBuffer, Vulkan::Buffer* indexBuffer, const std::string& text) {

    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;
    uint32_t indexOffset = 0;

    float width = texture->getWidth();
    float heigth = texture->getHeight();

    float posx = 0.0f;
    float posy = 0.0f;

    for (uint32_t i = 0; i < text.size(); i++) {
        Character *character = &characters[(int)text[i]];

        if (character->width == 0)
            character->width = 36;

        float charw = ((float)(character->width) / 36.0f);
        float dimx = 1.0f * charw;
        float charh = ((float)(character->height) / 36.0f);
        float dimy = 1.0f * charh;
        posy = 1.0f - charh;

        float us = character->x / width;
        float ue = (character->x + character->width) / width;
        float ts = character->y / heigth;
        float te = (character->y + character->height) / heigth;

        float xo = character->xoffset / 36.0f;
        float yo = character->yoffset / 36.0f;

        vertices.push_back({ { posx + dimx + xo,  posy + dimy, 0.0f }, { ue, te } });
        vertices.push_back({ { posx + xo,         posy + dimy, 0.0f }, { us, te } });
        vertices.push_back({ { posx + xo,         posy,        0.0f }, { us, ts } });
        vertices.push_back({ { posx + dimx + xo,  posy,        0.0f }, { ue, ts } });

        std::array<uint32_t, 6> letterIndices = { 0, 1, 2, 2, 3, 0 };

        for (auto& index : letterIndices) {
            indices.push_back(indexOffset + index);
        }

        indexOffset += 4;

        float advance = ((float)(character->xadvance) / 36.0f);
        posx += advance;
    }

    indexCount = indices.size();

    // Center
    for (auto& v : vertices) {
        v.pos.x -= posx / 2.0f;
        v.pos.y -= 0.5f;
    }

    vertexBuffer->write(vertices.data(), vertices.size() * sizeof(Vertex));
    indexBuffer->write(indices.data(), indices.size() * sizeof(uint32_t));

    return 0;
}
