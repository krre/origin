#pragma once
#include "Graphics/Color.h"
#include <string>
#include <vector>
#include <SDL.h>

const uint32_t WINDOW_WIDTH = 800;
const uint32_t WINDOW_HEIGHT = 600;

struct SDL_Window;
class Screen;

class RenderWindow {

public:
    RenderWindow();
    virtual ~RenderWindow();
    void init();

    void setX(int x) { this->x = x; }
    void setY(int y) { this->y = y; }
    int getX() const { return x; }
    int getY() const { return y; }
    uint32_t getWidth() const { return width; }
    uint32_t getHeight() const { return height; }

    SDL_Window* getHandle() const { return handle; }

    void pushScreen(const std::shared_ptr<Screen>& screen);
    void popScreen();
    void setScreen(const std::shared_ptr<Screen>& screen);

    void show();

    void update(float dt);
    virtual void render() = 0;

    void saveScreenshot();
    void toggleFullScreen();

protected:
    void onKeyPressed(const SDL_KeyboardEvent& event);
    void onMove(int x, int y);
    virtual void onResize(int width, int height);
    virtual void saveScreenshotImpl(const std::string& filePath) = 0;
    virtual Uint32 getSurfaceFlag() const = 0;

    SDL_Window* handle = nullptr;
    int x = 0;
    int y = 0;
    uint32_t width = WINDOW_WIDTH;
    uint32_t height = WINDOW_HEIGHT;

private:
    std::vector<std::shared_ptr<Screen>> screens;
};
