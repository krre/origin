#pragma once
#include "Screen.h"

class Button;

class SettingsScreen : public Screen {

public:
    SettingsScreen();

private:
    void resizeImpl(int width, int height) override;

    Button* buttonBack;
};
