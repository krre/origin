#pragma once
#include "resource/Resource.h"
#include <map>
#include <glm/glm.hpp>

namespace Vulkan {
    class Texture;
    class GpuBuffer;
}

class SDFFont : public Resource {
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

    SDFFont();
    ~SDFFont();

    void setSize(int size);
    int size() const { return m_size; }

    void load(const std::string& path) override;
    void renderText(Vulkan::GpuBuffer* vertexBuffer, Vulkan::GpuBuffer* indexBuffer, const std::string& text);
    Vulkan::Texture* texture() const { return m_texture.get(); }
    uint32_t indexCount() const { return m_indexCount; }


private:
    int m_size = 14;
    std::map<int, Character> m_characters;
    std::unique_ptr<Vulkan::Texture> m_texture;
    uint32_t m_indexCount;
    int m_maxCharacterWidth = 0;
    int m_avarageCharacterWidth = 0;
    int m_lineHeight;
    int m_base;
};
