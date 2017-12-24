#pragma once
#include "UI/Control.h"
#include "Graphics/Color.h"

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

    void prepareBatch(Batch2D* batch, VertexBuffer* vertexBuffer, IndexBuffer* indexBuffer) override;

private:
    void updateTextData();
    std::string text;
    Font* font;
    Color color = Color::BLACK;
};
