#pragma once
#include "Rectangle.h"
#include <SDL.h>

class Label;

class Button : public Rectangle {

public:
    Button();
    ~Button();
    void setText(const std::string& text);
    std::string getText() const;

    void setLabelColor(const Color& labelColor);
    const Color& getLabelColor() const;

    void prepareBatch(Batch2D* batch, VertexBuffer* vertexBuffer, IndexBuffer* indexBuffer) override;

    Signal<> clicked;

private:
    void onMouseButtonAction(const SDL_MouseButtonEvent& event);
    std::shared_ptr<Label> label;
    int clickedId;
};
