#pragma once
#include "Rectangle.h"
#include "Text/Label.h"
#include <SDL.h>

class Button : public Rectangle {

public:
    Button();
    ~Button();
    void setText(const std::string& text);
    std::string getText() const { return label->getText(); }

    void setLabelColor(const Color& labelColor);
    const Color& getLabelColor() const { return label->getColor(); }

    void prepareBatch(Batch2D* batch) override;

    Nano::Signal<void()> clicked;

protected:
    void draw(float dt) override;

private:
    void onMouseButtonAction(const SDL_MouseButtonEvent& event);
    std::shared_ptr<Label> label;
};
