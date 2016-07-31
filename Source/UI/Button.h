#pragma once
#include "Rectangle.h"
#include "Text.h"
#include <SDL.h>

class Button : public Rectangle {

public:
    Button();
    ~Button();
    void setText(const std::string& text);
    std::string getText() const { return text; }

    Nano::Signal<void()> clicked;

protected:
    void draw(float dt) override;

private:
    void onMouseButtonAction(const SDL_MouseButtonEvent& event);
    std::string text;
    Text labelText;
};
