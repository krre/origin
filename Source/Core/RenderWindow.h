#pragma once
#include <string>
#include "Graphics/Render/RenderTarget.h"

const uint32_t WINDOW_WIDTH = 800;
const uint32_t WINDOW_HEIGHT = 600;

struct SDL_Window;

class RenderWindow : public RenderTarget {

public:
    RenderWindow();
    ~RenderWindow();

    void setX(int x) { this->x = x; }
    void setY(int y) { this->y = y; }
    int getX() const { return x; }
    int getY() const { return y; }

    void show();
    void create();

    SDL_Window* getHandle() { return handle; }

private:
    SDL_Window* handle = nullptr;
    int x = 100;
    int y = 100;

    void onMove(int x, int y);
    void onResize(int width, int height);
};
