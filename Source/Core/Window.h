#pragma once
#include <string>

struct SDL_Window;

class Window {

public:
    Window();
    ~Window();

    void setX(int x) { this->x = x; }
    void setY(int y) { this->y = y; }
    int getX() const { return x; }
    int getY() const { return y; }

    void setWidth(int width) { this->width = width; }
    void setHeight(int height) { this->height = height; }
    int getWidth() const { return width; }
    int getHeight() const { return height; }

    void show();
    void create();

    SDL_Window* getHandle() { return handle; }

private:
    SDL_Window* handle = nullptr;
    int x = 100;
    int y = 100;
    int width = 800;
    int height = 600;

    void onMove(int x, int y);
    void onResize(int width, int height);
};
