#pragma once
#include "Control.h"
#include "Graphics/Color.h"

namespace Origin {

class Font;

class Rectangle : public Control {

public:
    Rectangle(Control* parent = nullptr);
    Rectangle(const Core::Size& size, Control* parent = nullptr);
    Rectangle(const Core::Pos2& position, const Core::Size& size, Control* parent = nullptr);

    void setColor(const Color& color);
    const Color& getColor() const { return color; }

    void setBorderColor(const Color& borderColor);
    const Color& getBorderColor() const { return borderColor; }

    void setBorderWidth(uint32_t borderWidth);
    uint32_t getBorderWidth() const { return borderWidth; }

private:
    void drawImpl() override;

    Color color = Color::WHITE;
    Color borderColor = Color::GRAY;
    uint32_t borderWidth = 0;
    Font* font;
};

} // Origin
