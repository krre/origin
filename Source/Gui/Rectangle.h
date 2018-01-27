#pragma once
#include "Control.h"
#include "Graphics/Color.h"

namespace Origin {

class Rectangle : public Control {

public:
    Rectangle(const Size& size, Control* parent = nullptr);
    Rectangle(const Pos2& position, const Size& size, Control* parent = nullptr);

    void setColor(const Color& color);
    const Color& getColor() const { return color; }

    void setBorderColor(const Color& borderColor);
    const Color& getBorderColor() const { return borderColor; }

    void setBorderWidth(uint32_t borderWidth);
    uint32_t getBorderWidth() const { return borderWidth; }

    void prepareBatch(std::vector<Batch2D>& batches, std::vector<Batch2D::Vertex>& vertices) override;

private:
    void drawImpl() override;

    Color color = Color::WHITE;
    Color borderColor = Color::GRAY;
    uint32_t borderWidth = 0;
};

} // Origin
