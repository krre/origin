#pragma once
#include "../Core/Object.h"
#include <vector>

class Texture : public Object {

public:
    Texture(const std::string& path);
    uint32_t getWidth() const { return width; }
    uint32_t getHeight() const { return height; }

private:
    std::vector<unsigned char> data;
    uint32_t width = 0;
    uint32_t height = 0;
};
