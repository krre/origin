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

    int charactersCount = 0;
    int charactersWidthSum = 0;

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
                    if (value) {
                        charactersWidthSum += value;
                        charactersCount++;
                        maxCharacterWidth = std::max(maxCharacterWidth, value);
                    }
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

    assert(!characters.empty());

    avarageCharacterWidth = charactersWidthSum / charactersCount;
}

void Font::renderText(Vulkan::Buffer* vertexBuffer, Vulkan::Buffer* indexBuffer, const std::string& text) {
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;
    uint32_t indexOffset = 0;
    const int verticesPerCharacter = 4;

    float width = texture->getWidth();
    float heigth = texture->getHeight();

    int posx = 0;
    int posy = 0;

    for (auto& sign : text) {
        Character* character = &characters[(int)sign];

        if (character->width == 0) {
            character->width = maxCharacterWidth / 2;
        }

        float us = character->x / width;
        float ue = (character->x + character->width) / width;
        float ts = character->y / heigth;
        float te = (character->y + character->height) / heigth;

        int xo = character->xoffset;
        int yo = character->yoffset;

        vertices.push_back({ { posx + character->width + xo, posy + character->height + yo, 0.0f }, { ue, te } });
        vertices.push_back({ { posx + xo, posy + character->height + yo, 0.0f }, { us, te } });
        vertices.push_back({ { posx + xo, posy + yo, 0.0f }, { us, ts } });
        vertices.push_back({ { posx + character->width + xo, posy + yo, 0.0f }, { ue, ts } });

        std::vector<uint32_t> characterIndices = { 0, 1, 2, 2, 3, 0 };

        for (auto& index : characterIndices) {
            indices.push_back(indexOffset + index);
        }

        indexOffset += verticesPerCharacter;
        posx += character->width + xo;
    }

    indexCount = indices.size();

    vertexBuffer->write(vertices.data(), vertices.size() * sizeof(Vertex));
    indexBuffer->write(indices.data(), indices.size() * sizeof(uint32_t));
}
