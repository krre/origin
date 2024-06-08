#pragma once
#include "Screen.h"

class Button;
class LinearLayout;
class ListBox;

class LoadWorldScreen : public Screen {

public:
    LoadWorldScreen();

private:
    void resizeImpl(int width, int height) override;

    Button* m_buttonBack;
    LinearLayout* m_layout;
    ListBox* m_listBox;
};
