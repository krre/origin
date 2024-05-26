#pragma once
#include "Screen.h"

class WaitScreen : public Screen {

public:
    WaitScreen();

private:
    void resizeImpl(int width, int height) override;
};
