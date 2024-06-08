#pragma once
#include "Screen.h"

class LinearLayout;

class MenuScreen : public Screen {

public:
    MenuScreen();

private:
    void resizeImpl(int width, int height) override;

    LinearLayout* m_layout;
};
