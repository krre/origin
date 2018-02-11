#pragma once
#include "UI/Rectangle.h"

namespace Origin {

class LinearLayout;
class Label;
class ListBox;

class ListLine : public Rectangle {

public:
    ListLine(const std::string& text, int index, ListBox* listBox);
    int getIndex() const { return index; }

private:
    void mouseButtonAction(const SDL_MouseButtonEvent& event);

    Label* label;
    ListBox* listBox;
    int index;
};

class ListBox : public Rectangle {
    friend class ListLine;

public:
    ListBox(Control* parent = nullptr);
    ~ListBox();
    void addLine(const std::string& text);
    void setCurrentIndex(int currentIndex);
    const std::string& getCurrentText() const { return currentText; }

private:
    void resizeImpl(int width, int height) override;

    LinearLayout* layout;
    std::string currentText;
    int currentIndex = -1;
};

} // Origin
