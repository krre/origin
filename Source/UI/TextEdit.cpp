#include "TextEdit.h"
#include "Rectangle.h"
#include "Label.h"

namespace Origin {

const Color BACKGROUND_COLOR = Color(0, 0, 0, 0.8);

TextEdit::TextEdit(Control* parent) : Control(parent) {
    background = new Rectangle(Size(200, 20), this);
    background->setColor(BACKGROUND_COLOR);

    label = new Label(this);
    label->setColor(Color(0.85, 0.85, 0.85));
    label->setText("test line");
    label->setPosition(Pos2(0, 15));
}

} // Origin
