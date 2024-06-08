#pragma once
#include "graphics/Color.h"
#include <core/SingleObject.h>
#include <vector>
#include <functional>

#undef HAVE_STDINT_H

struct SDL_Window;
struct SDL_KeyboardEvent;

class Screen;

class Window : public Core::SingleObject<Window> {
public:
    Window(Object* parent = nullptr);
    ~Window();

    uint32_t width() const { return m_width; }
    uint32_t height() const { return m_height; }

    SDL_Window* handle() const { return m_handle; }

    void pushScreen(const std::shared_ptr<Screen>& screen);
    void popScreen();
    void setScreen(const std::shared_ptr<Screen>& screen);
    Screen* currentScreen() const;

    void show();
    void close();

    void update(float dt);
    void render();
    void onResize(int width, int height);
    void toggleFullScreen();

    void setColor(const Color& color);
    const Color& color() const { return m_color; }

    void invokeDeffered();

private:
    // Save call deffered funtions, e.g. destroy screen.
    void addDeferredCall(const std::function<void()>& defferedCall) { m_deferredCalls.push_back(defferedCall); }
    void onKeyPressed(const SDL_KeyboardEvent& event);

    SDL_Window* m_handle = nullptr;
    uint32_t m_width = 800;
    uint32_t m_height = 600;
    std::vector<std::shared_ptr<Screen>> m_screens;
    Color m_color = Color(0.42, 0.65, 5.0, 1.0);
    std::vector<std::function<void()>> m_deferredCalls;
};
