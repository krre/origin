#pragma once
#include "Core/Screen.h"

class Scene;

class MenuScreen : public Screen {

public:
    MenuScreen();

private:
    std::shared_ptr<Scene> menuScene;
};
