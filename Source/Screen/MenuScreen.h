#pragma once
#include "Screen.h"

namespace Origin {

class LinearLayout;

class MenuScreen : public Screen {

public:
    MenuScreen();

private:
    void resizeImpl(int width, int height) override;

    LinearLayout* layout;
};

} // Origin
