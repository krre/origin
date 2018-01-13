#pragma once
#include "UI/Control.h"
#include "Graphics/Color.h"

namespace Origin {

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

    void prepareBatch(std::vector<Batch2D>& batches, std::vector<float>& vertices) override;

private:
    void updateTextData();
    std::string text;
    Font* font;
    Color color = Color::BLACK;
};

} // Origin
