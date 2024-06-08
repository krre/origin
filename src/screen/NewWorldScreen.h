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

    TextEdit* m_textEdit = nullptr;
    Button* m_buttonBack = nullptr;
    LinearLayout* m_layout = nullptr;
};
