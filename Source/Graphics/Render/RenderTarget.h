#pragma once
#include "Core/Common.h"

class RenderTarget {

public:
    RenderTarget();
    void setWidth(uint32_t width) { this->width = width; }
    void setHeight(uint32_t height) { this->height = height; }
    uint32_t getWidth() const { return width; }
    uint32_t getHeight() const { return height; }

protected:
    uint32_t width = 0;
    uint32_t height = 0;
};
