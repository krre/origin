#pragma once
#include "ui/Rectangle.h"

class LinearLayout;
class Label;
class ListBox;

class RowDelegate : public Rectangle {
public:
    RowDelegate(const std::string& text, int index, ListBox* listBox);
    int index() const { return m_index; }

private:
    void mouseButtonAction(const SDL_MouseButtonEvent& event);

    Label* m_label;
    ListBox* m_listBox;
    int m_index;
};

class ListBox : public Rectangle {
    friend class RowDelegate;
public:
    ListBox(Control* parent = nullptr);

    void addLine(const std::string& text);
    void removeLine(int index);

    void setCurrentIndex(int currentIndex);
    int currentIndex() const { return m_currentIndex; }

    const std::string& currentText() const { return m_currentText; }

private:
    void resizeImpl(int width, int height) override;

    LinearLayout* m_layout = nullptr;
    std::string m_currentText;
    int m_currentIndex = -1;
};
