#pragma once
#include "Rectangle.h"
#include <SDL.h>

namespace Origin {

class Label;

class Button : public Rectangle {

public:
    Button(Control* parent = nullptr);
    Button(const std::string& text, Control* parent = nullptr);
    ~Button();
    void setText(const std::string& text);
    std::string getText() const;

    void setTextColor(const Color& labelColor);
    const Color& getTextColor() const;

    Signal<> clicked;

private:
    void onMouseButtonAction(const SDL_MouseButtonEvent& event);
    void centerLabel();
    void resizeImpl(int width, int height) override;

    Label* label;
    int clickedId;
};

} // Origin
