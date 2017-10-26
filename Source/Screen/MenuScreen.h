#pragma once
#include "Core/Screen.h"

class View2D;

class MenuScreen : public Screen {

public:
    MenuScreen();

private:
    std::shared_ptr<View2D> menuView;
};
