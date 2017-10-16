#pragma once
#include "Core/Screen.h"

class MenuScreen : public Screen {

public:
    MenuScreen();

    void resize(uint32_t width, uint32_t height) override;
};
