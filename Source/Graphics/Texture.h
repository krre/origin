#pragma once
#include "../Core/Object.h"
#include <vector>

class Texture : public Object {

public:
    Texture(const std::string& path);

private:
    std::vector<unsigned char> data;
    uint32_t width;
    uint32_t height;
};
