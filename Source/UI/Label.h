#pragma once
#include "Control.h"
#include "Graphics/Color.h"

class Font;

class Label : public Control {

public:
    Label(Control* parent = nullptr);
    Label(const std::string& text, Control* parent = nullptr);
    void setText(const std::string& text);
    const std::string& getText() const { return text; }

    void setFont(Font* font);
    Font* getFont() const { return font; }

    void setColor(const Color& color);
    const Color& getColor() const { return color; }

private:
    void drawImpl() override;

    std::string text;
    Font* font;
    Color color = Color::BLACK;
    int lineCount = 0;
};
