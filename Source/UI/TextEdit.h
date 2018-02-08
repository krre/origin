#pragma once
#include "Control.h"

namespace Origin {

class Rectangle;
class Label;

class TextEdit : public Control {

public:
    TextEdit(Control* parent = nullptr);

private:
    Rectangle* background;
    Label* label;

};

} // Origin
