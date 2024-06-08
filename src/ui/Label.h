#pragma once
#include "Control.h"
#include "graphics/Color.h"

class Font;

class Label : public Control {
public:
    Label(Control* parent = nullptr);
    Label(const std::string& text, Control* parent = nullptr);

    void setText(const std::string& text);
    const std::string& text() const { return m_text; }

    void setFont(Font* font);
    Font* font() const { return m_font; }

    void setColor(const Color& color);
    const Color& color() const { return m_color; }

private:
    void drawImpl() override;

    std::string m_text;
    Font* m_font;
    Color m_color = Color::BLACK;
    int m_lineCount = 0;
};
