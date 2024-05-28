#pragma once
#include "ui/Rectangle.h"

class LinearLayout;
class Label;
class ListBox;

class RowDelegate : public Rectangle {

public:
    RowDelegate(const std::string& text, int index, ListBox* listBox);
    int getIndex() const { return index; }

private:
    void mouseButtonAction(const SDL_MouseButtonEvent& event);

    Label* label;
    ListBox* listBox;
    int index;
};

class ListBox : public Rectangle {
    friend class RowDelegate;

public:
    ListBox(Control* parent = nullptr);
    ~ListBox();
    void addLine(const std::string& text);
    void removeLine(int index);

    void setCurrentIndex(int currentIndex);
    int getCurrentIndex() const { return currentIndex; }

    const std::string& getCurrentText() const { return currentText; }

private:
    void resizeImpl(int width, int height) override;

    LinearLayout* layout;
    std::string currentText;
    int currentIndex = -1;
};
