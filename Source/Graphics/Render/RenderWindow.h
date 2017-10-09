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

    virtual void swapBuffers() = 0;
    virtual void saveImage(const std::string& filePath) = 0;
    virtual void createSurface() {}

    SDL_Window* getHandle() { return handle; }

protected:
    SDL_Window* handle = nullptr;

private:
    int x = 100;
    int y = 100;

    void onMove(int x, int y);
    void onResize(int width, int height);
};
