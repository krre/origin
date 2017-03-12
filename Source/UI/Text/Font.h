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
        int heigth;
        int xoffset;
        int yoffset;
        int xadvance;
    } character;

    Font();
    ~Font();
    void setSize(int size);
    int getSize() const { return size; }
    void load(const std::string& path) override;
    int renderText(Vulkan::Buffer* buffer, const std::string& text, float x, float y);
    void uploadTexture(Vulkan::DeviceMemory* memory);

private:
    int size = 14;
    std::map<int, Character> characters;
    std::shared_ptr<Texture> texture;
};
