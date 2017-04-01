#pragma once
#include "../../Resource/Resource.h"
#include "../../Graphics/Vulkan/Buffer.h"
#include "../../Graphics/Texture.h"
#include <map>
#include <glm/glm.hpp>

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

    struct Vertex {
        glm::vec3 pos;
        glm::vec2 uv;
    };

    Font();
    ~Font();
    void setSize(int size);
    int getSize() const { return size; }
    void load(const std::string& path) override;
    void renderText(Vulkan::Buffer* vertexBuffer, Vulkan::Buffer* indexBuffer, const std::string& text);
    Texture* getTexture() const { return texture.get(); }
    uint32_t getIndexCount() const { return indexCount; }


private:
    int size = 14;
    std::map<int, Character> characters;
    std::shared_ptr<Texture> texture;
    uint32_t indexCount;
    int maxCharacterWidth = 0;
    int avarageCharacterWidth = 0;
};
