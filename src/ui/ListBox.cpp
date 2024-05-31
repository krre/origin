#include "ListBox.h"
#include "LinearLayout.h"
#include "Label.h"

#undef HAVE_STDINT_H
#include <SDL_events.h>

const Color LINE_SELECTED_COLOR = Color(1, 1, 1, 0.3);
const Color LINE_COLOR = Color(0, 0, 0, 0.7);

RowDelegate::RowDelegate(const std::string& text, int index, ListBox* listBox) :
        m_index(index),
        listBox(listBox) {
    setColor(LINE_COLOR);
    label = new Label(text, this);
    label->setColor(Color::WHITE);
    resize(200, 30);
    // Align to vertical center
    label->move(5, (size().height - label->contentHeight()) / 2);
}

void RowDelegate::mouseButtonAction(const SDL_MouseButtonEvent& event) {
     if (event.type == SDL_MOUSEBUTTONDOWN) {
        listBox->m_currentText = label->text();
        listBox->setCurrentIndex(m_index);
     }
}

ListBox::ListBox(Control* parent) : Rectangle(parent) {
    setColor(Color(0, 0, 0, 0.6));
    layout = new LinearLayout(LinearLayout::Direction::Vertical, this);
}

ListBox::~ListBox() {

}

void ListBox::addLine(const std::string& text) {
    RowDelegate* listLine = new RowDelegate(text, layout->getChildren().size(), this);
    layout->appendChild(listLine);
}

void ListBox::removeLine(int index) {
    layout->removeChild(index);
    m_currentIndex = -1;
}

void ListBox::setCurrentIndex(int currentIndex) {
    this->m_currentIndex = currentIndex;

    for (Object* child : layout->getChildren()) {
        RowDelegate* listLine = static_cast<RowDelegate*>(child);
        if (listLine->index() == currentIndex) {
            listLine->setColor(LINE_SELECTED_COLOR);
        } else {
            listLine->setColor(LINE_COLOR);
        }
    }
}

void ListBox::resizeImpl(int width, int height) {
    layout->resize(width, height);
}
