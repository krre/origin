#pragma once
#include <SDL.h>

class Window {

public:
    Window();

    void setX(int x) { this->x = x; }
    void setY(int y) { this->y = y; }
    int getX() const { return x; }
    int getY() const { return y; }

    void setWidth(int width) { this->width = width; }
    void setHeight(int height) { this->height = height; }
    int getWidth() const { return width; }
    int getHeight() const { return height; }

private:
    int x = 0;
    int y = 0;
    int width = 100;
    int height = 100;
};
