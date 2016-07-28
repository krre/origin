#pragma once
#include "Rectangle.h"
#include "Text.h"

class Button : public Rectangle {

public:
    Button();
    void setText(const std::string& text);
    std::string getText() const { return text; }

    Nano::Signal<void()> clicked;

protected:
    void draw(float dt) override;

private:
    std::string text;
    Text labelText;
};
