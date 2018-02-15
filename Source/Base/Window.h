#pragma once
#include "Core/Object.h"
#include "Graphics/Color.h"
#include <string>
#include <vector>
#include <functional>

#undef HAVE_STDINT_H
#include <SDL.h>

struct SDL_Window;

namespace Origin {

class Screen;

class Window : public Object {

public:
    Window(Object* parent = nullptr);
    ~Window();

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
    Screen* getCurrentScreen() const;

    void show();
    void update(float dt);
    void render();
    void onResize(int width, int height);
    void toggleFullScreen();
    void setColor(const Color& color);
    const Color& getColor() const { return color; }

    void invokeDeffered();

private:
    // Save call deffered funtions, e.g. destroy screen.
    void addDeferredCall(const std::function<void()>& defferedCall) { deferredCalls.push_back(defferedCall); }
    void onKeyPressed(const SDL_KeyboardEvent& event);
    void onMove(int x, int y);

    SDL_Window* handle = nullptr;
    int x = 0;
    int y = 0;
    uint32_t width = 800;
    uint32_t height = 600;
    std::vector<std::shared_ptr<Screen>> screens;
    Color color = Color(0.9, 1.0, 1.0, 1.0);
    std::vector<std::function<void()>> deferredCalls;
};

} // Origin
