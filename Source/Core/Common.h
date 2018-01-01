#pragma once
#include <iostream>
#include <memory>
#ifndef QT_VERSION
    #include "Signal.h"
    #define PRINT(x) std::cout << x << std::endl;
    #define ERROR(x) std::cerr << x << std::endl;
#endif

constexpr int PAGE_BYTES = 1 << 13; // 8192 (use in OctreeFarm)
const int BLOCK_INFO_END = 1;

using EntityId = uint64_t;

enum class GameScreen {
    MENU,
    SETTINGS,
    GAME
};

struct Size {
    Size() = default;
    Size(uint32_t width, uint32_t height) : width(width), height(height) {}
    uint32_t width;
    uint32_t height;
};

struct Pos2 {
    int x;
    int y;

    Pos2 operator+(const Pos2& pos) const { return { pos.x + x, pos.y + y }; }
};

struct Pos2F {
    float x;
    float y;

    Pos2F operator+(const Pos2F& pos) const { return { pos.x + x, pos.y + y }; }
};

struct Rect {
    int x;
    int y;
    int width;
    int height;
};

struct RectF {
    float x;
    float y;
    float width;
    float height;
};
