#pragma once
#include "Rectangle.h"

class Button : public Rectangle {

public:
    Button();
    void setText(const std::string& text);
    std::string getText() const { return text; }

    Nano::Signal<void()> clicked;

private:
    std::string text;
};
