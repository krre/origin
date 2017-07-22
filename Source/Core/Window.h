#pragma once
#include <SDL.h>

class Window {

public:
    Window();

    void setWidth(int width);
    void setHeight(int height);
    int getWidth() const;
    int getHeight() const;

private:
    int width = 100;
    int height = 100;
};
