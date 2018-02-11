#include "ListBox.h"
#include "LinearLayout.h"
#include "Label.h"

#undef HAVE_STDINT_H
#include <SDL_events.h>

namespace Origin {

ListLine::ListLine(const std::string& text, Control* parent) : Rectangle(parent) {
    setColor(Color(0, 0, 0, 0.7));
    label = new Label(text, this);
    label->setColor(Color::WHITE);
    resize(200, 30);
}

void ListLine::mouseButtonAction(const SDL_MouseButtonEvent& event) {
     if (event.type == SDL_MOUSEBUTTONDOWN) {
        PRINT(label->getText())
     }
}

ListBox::ListBox(Control* parent) : Rectangle(parent) {
    layout = new LinearLayout(LinearLayout::Direction::Vertical, this);
}

ListBox::~ListBox() {

}

void ListBox::addLine(const std::string& text) {
    ListLine* listLine = new ListLine(text, this);
    layout->addControl(listLine);
}

void ListBox::resizeImpl(int width, int height) {
    layout->resize(width, height);
}



} // Origin
