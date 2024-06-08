#pragma once
#include "Screen.h"

class TextEdit;
class Button;
class LinearLayout;

class NewWorldScreen : public Screen {

public:
    NewWorldScreen();

private:
    void resizeImpl(int width, int height) override;

    TextEdit* m_textEdit;
    Button* m_buttonBack;
    LinearLayout* m_layout;
};
