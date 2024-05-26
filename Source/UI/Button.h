#pragma once
#include "Rectangle.h"

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

    Core::Signal<> clicked;

private:
    void mouseButtonAction(const SDL_MouseButtonEvent& event) override;

    void centerLabel();
    void resizeImpl(int width, int height) override;

    Label* label;
    int clickedId;
};
