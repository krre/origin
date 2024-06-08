#pragma once
#include "Control.h"
#include "graphics/Color.h"

class Font;

class Rectangle : public Control {

public:
    Rectangle(Control* parent = nullptr);
    Rectangle(const Core::Size& size, Control* parent = nullptr);
    Rectangle(const Core::Pos2& position, const Core::Size& size, Control* parent = nullptr);

    void setColor(const Color& color);
    const Color& color() const { return m_color; }

    void setBorderColor(const Color& borderColor);
    const Color& borderColor() const { return m_borderColor; }

    void setBorderWidth(uint32_t borderWidth);
    uint32_t borderWidth() const { return m_borderWidth; }

private:
    void drawImpl() override;

    Color m_color = Color::WHITE;
    Color m_borderColor = Color::GRAY;
    uint32_t m_borderWidth = 0;
    Font* m_font;
};
