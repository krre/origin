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

    Button* m_buttonBack = nullptr;
    LinearLayout* m_layout = nullptr;
    ListBox* m_listBox = nullptr;
};
