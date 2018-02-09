#pragma once
#include "Screen.h"

namespace Origin {

class TextEdit;

class NewWorldScreen : public Screen {

public:
    NewWorldScreen();

private:
    TextEdit* textEdit;
};

} // Origin
