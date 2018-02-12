#include "ListBox.h"
#include "LinearLayout.h"
#include "Label.h"

#undef HAVE_STDINT_H
#include <SDL_events.h>

namespace Origin {

const Color LINE_SELECTED_COLOR = Color(1, 1, 1, 0.3);
const Color LINE_COLOR = Color(0, 0, 0, 0.7);

ListLine::ListLine(const std::string& text, int index, ListBox* listBox) :
        index(index),
        listBox(listBox) {
    setColor(LINE_COLOR);
    label = new Label(text, this);
    label->setColor(Color::WHITE);
    resize(200, 30);
}

void ListLine::mouseButtonAction(const SDL_MouseButtonEvent& event) {
     if (event.type == SDL_MOUSEBUTTONDOWN) {
        listBox->currentText = label->getText();
        listBox->setCurrentIndex(index);
     }
}

ListBox::ListBox(Control* parent) : Rectangle(parent) {
    setColor(Color(0, 0, 0, 0.6));
    layout = new LinearLayout(LinearLayout::Direction::Vertical, this);
}

ListBox::~ListBox() {

}

void ListBox::addLine(const std::string& text) {
    ListLine* listLine = new ListLine(text, layout->getChildren().size(), this);
    layout->addChild(listLine);
}

void ListBox::removeLine(int index) {
    layout->removeChild(index);
}

void ListBox::setCurrentIndex(int currentIndex) {
    this->currentIndex = currentIndex;

    for (Object* child : layout->getChildren()) {
        ListLine* listLine = static_cast<ListLine*>(child);
        if (listLine->getIndex() == currentIndex) {
            listLine->setColor(LINE_SELECTED_COLOR);
        } else {
            listLine->setColor(LINE_COLOR);
        }
    }
}

void ListBox::resizeImpl(int width, int height) {
    layout->resize(width, height);
}



} // Origin
