#pragma once
#include "../Control.h"
#include "../../Graphics/Color.h"

class Font;

class Label : public Control {

public:
    Label();
    void setText(const std::string& text);
    const std::string& getText() const { return text; }

    void setFont(Font* font);
    Font* getFont() const { return font; }

    void setColor(const Color& color);
    const Color& getColor() const { return color; }

    void draw(float dt) override;
    void update(float dt) override;

private:
    void updateTextData();
    std::string text;
    Font* font;
    Color color = { 1.0, 1.0, 1.0 };
};
