#pragma once
#include <iostream>
#include <memory>
#include "Defines.h"
#ifndef QT_VERSION
    #include "Signal.h"
    #define PRINT(x) std::cout << x << std::endl;
#endif

namespace Core {

constexpr int PAGE_BYTES = 1 << 13; // 8192 (use in OctreeFarm)
const int BLOCK_INFO_END = 1;

using EntityId = uint64_t;

struct Size {
    Size() = default;
    Size(uint32_t width, uint32_t height) : width(width), height(height) {}
    uint32_t width;
    uint32_t height;
};

struct Pos2 {
    Pos2(int x, int y) : x(x), y(y) {}
    int x = 0;
    int y = 0;

    Pos2 operator+(const Pos2& pos) const { return { pos.x + x, pos.y + y }; }
};

struct Pos2F {
    float x;
    float y;

    Pos2F operator+(const Pos2F& pos) const { return { pos.x + x, pos.y + y }; }
};

struct Rect {
    Rect() = default;
    Rect(int x, int y, int width, int height):
        x(x), y(y), width(width), height(height) {}
    int x = 0;
    int y = 0;
    int width = 0;
    int height = 0;
};

struct RectF {
    float x;
    float y;
    float width;
    float height;
};

}
