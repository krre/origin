#pragma once
#include "UI/Rectangle.h"

namespace Origin {

class LinearLayout;
class Label;

class ListLine : public Rectangle {

public:
    ListLine(const std::string& text, Control* parent = nullptr);

private:
    void mouseButtonAction(const SDL_MouseButtonEvent& event);

    Label* label;
};

class ListBox : public Rectangle {

public:
    ListBox(Control* parent = nullptr);
    ~ListBox();
    void addLine(const std::string& text);

private:
    void resizeImpl(int width, int height) override;

    LinearLayout* layout;
};

} // Origin
