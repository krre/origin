#pragma once
#include "Graphics/Render/RenderTarget.h"
#include "Graphics/Color.h"
#include <string>

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

    void setColor(const Color& color);
    const Color& getColor() const { return color; }

    void show();

    virtual void clear() = 0;
    virtual void swapBuffers() = 0;
    virtual void saveImage(const std::string& filePath) = 0;

    SDL_Window* getHandle() { return handle; }

protected:
    virtual void resize(int width, int height) = 0;
    virtual void setColorImpl(const Color& color) = 0;
    SDL_Window* handle = nullptr;
    int x = 100;
    int y = 100;

private:
    void onMove(int x, int y);
    void onResize(int width, int height);

    Color color = Color::WHITE;
};
