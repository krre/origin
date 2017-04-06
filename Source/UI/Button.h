#pragma once
#include "Rectangle.h"
#include "Text/Label.h"
#include <SDL.h>

class Button : public Rectangle {

public:
    Button();
    ~Button();
    void setText(const std::string& text);
    std::string getText() const { return label.getText(); }

    Nano::Signal<void()> clicked;

protected:
    void draw(float dt) override;

private:
    void onMouseButtonAction(const SDL_MouseButtonEvent& event);
    Label label;
};
