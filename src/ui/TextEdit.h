#pragma once
#include "Control.h"

class Rectangle;
class Label;

class TextEdit : public Control {

public:
    TextEdit(Control* parent = nullptr);

    void setText(const std::string& text);
    const std::string& text() const;

protected:
    void keyPressed(const SDL_KeyboardEvent& event) override;
    void textPressed(const SDL_TextInputEvent& event) override;
    void mouseButtonAction(const SDL_MouseButtonEvent& event) override;

private:
    void resizeImpl(int width, int height) override;

    Rectangle* background;
    Label* label;
    int cursorPosition = 0;
};
