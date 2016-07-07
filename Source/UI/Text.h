#pragma once
#include "Control.h"

class Text : public Control {

public:
    Text();
    void setText(const string& text);
    string getText() const { return text; }

private:
    string text;
};
