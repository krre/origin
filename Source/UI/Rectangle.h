#pragma once
#include "Control.h"
#include "Graphics/Color.h"

namespace Origin {

class Rectangle : public Control {

public:
    Rectangle(const Size& size);
    Rectangle(const Pos2& position, const Size& size);

    void setColor(const Color& color);
    const Color& getColor() const { return color; }

    void setBorderColor(const Color& borderColor);
    const Color& getBorderColor() const { return borderColor; }

    void setBorderWidth(uint32_t borderWidth);
    uint32_t getBorderWidth() const { return borderWidth; }

    void prepareBatch(Batch2D* batch, VertexBuffer* vertexBuffer, IndexBuffer* indexBuffer) override;

private:
    Color color = Color::WHITE;
    Color borderColor = Color::GRAY;
    uint32_t borderWidth = 0;
};

} // Origin
