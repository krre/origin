#include "ListBox.h"
#include "LinearLayout.h"
#include "Label.h"

#undef HAVE_STDINT_H
#include <SDL_events.h>

const Color LINE_SELECTED_COLOR = Color(1, 1, 1, 0.3);
const Color LINE_COLOR = Color(0, 0, 0, 0.7);

RowDelegate::RowDelegate(const std::string& text, int index, ListBox* listBox) :
        m_index(index),
        m_listBox(listBox) {
    setColor(LINE_COLOR);
    m_label = new Label(text, this);
    m_label->setColor(Color::WHITE);
    resize(200, 30);
    // Align to vertical center
    m_label->move(5, (size().height - m_label->contentHeight()) / 2);
}

void RowDelegate::mouseButtonAction(const SDL_MouseButtonEvent& event) {
     if (event.type == SDL_MOUSEBUTTONDOWN) {
        m_listBox->m_currentText = m_label->text();
        m_listBox->setCurrentIndex(m_index);
     }
}

ListBox::ListBox(Control* parent) : Rectangle(parent) {
    setColor(Color(0, 0, 0, 0.6));
    m_layout = new LinearLayout(LinearLayout::Direction::Vertical, this);
}

ListBox::~ListBox() {

}

void ListBox::addLine(const std::string& text) {
    RowDelegate* listLine = new RowDelegate(text, m_layout->children().size(), this);
    m_layout->appendChild(listLine);
}

void ListBox::removeLine(int index) {
    m_layout->removeChild(index);
    m_currentIndex = -1;
}

void ListBox::setCurrentIndex(int currentIndex) {
    m_currentIndex = currentIndex;

    for (Object* child : m_layout->children()) {
        RowDelegate* listLine = static_cast<RowDelegate*>(child);
        if (listLine->index() == currentIndex) {
            listLine->setColor(LINE_SELECTED_COLOR);
        } else {
            listLine->setColor(LINE_COLOR);
        }
    }
}

void ListBox::resizeImpl(int width, int height) {
    m_layout->resize(width, height);
}
