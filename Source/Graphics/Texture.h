#pragma once
#include "Core/Object.h"

namespace Origin {

class Texture : public Object {

public:
    Texture(const std::string& path);
    uint32_t getWidth() const { return width; }
    uint32_t getHeight() const { return height; }

private:
    uint32_t width = 0;
    uint32_t height = 0;
};

} // Origin
