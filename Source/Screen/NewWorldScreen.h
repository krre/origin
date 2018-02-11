#pragma once
#include "Screen.h"

namespace Origin {

class TextEdit;
class Button;
class LinearLayout;

class NewWorldScreen : public Screen {

public:
    NewWorldScreen();

private:
    void resizeImpl(int width, int height) override;

    TextEdit* textEdit;
    Button* buttonBack;
    LinearLayout* layout;
};

} // Origin
