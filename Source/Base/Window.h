#pragma once
#include "Core/SingleObject.h"
#include "Graphics/Color.h"
#include <string>
#include <vector>
#include <functional>

#undef HAVE_STDINT_H
#include <SDL.h>

struct SDL_Window;

namespace Origin {

class Screen;

class Window : public SingleObject<Window> {

public:
    Window(Object* parent = nullptr);
    ~Window();

    uint32_t getWidth() const { return width; }
    uint32_t getHeight() const { return height; }

    SDL_Window* getHandle() const { return handle; }

    void pushScreen(const std::shared_ptr<Screen>& screen);
    void popScreen();
    void setScreen(const std::shared_ptr<Screen>& screen);
    Screen* getCurrentScreen() const;

    void show();
    void close();

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

    SDL_Window* handle = nullptr;
    uint32_t width = 800;
    uint32_t height = 600;
    std::vector<std::shared_ptr<Screen>> screens;
    Color color = Color(0.42, 0.65, 5.0, 1.0);
    std::vector<std::function<void()>> deferredCalls;
};

} // Origin
