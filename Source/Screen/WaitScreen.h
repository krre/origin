#pragma once
#include "Screen.h"

namespace Origin {

class WaitScreen : public Screen {

public:
    WaitScreen();

private:
    void resizeImpl(int width, int height) override;
};

} // Origin
