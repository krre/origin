#pragma once
#include "Resource/Resource.h"
#include <map>
#include <glm/glm.hpp>

class Texture;
class VertexBuffer;
class IndexBuffer;

namespace Vulkan {
    class Buffer;
}

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
    void renderText(VertexBuffer* vertexBuffer, IndexBuffer* indexBuffer, const std::string& text);
    Texture* getTexture() const { return texture.get(); }
    uint32_t getIndexCount() const { return indexCount; }


private:
    int size = 14;
    std::map<int, Character> characters;
    std::unique_ptr<Texture> texture;
    uint32_t indexCount;
    int maxCharacterWidth = 0;
    int avarageCharacterWidth = 0;
    int lineHeight;
    int base;
};
