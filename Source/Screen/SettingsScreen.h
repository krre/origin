#pragma once
#include "Screen.h"

namespace Origin {

class Button;

class SettingsScreen : public Screen {

public:
    SettingsScreen();

private:
    void resizeImpl(int width, int height) override;

    Button* buttonBack;
};

} // Origin
