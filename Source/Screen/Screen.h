#pragma once
#include "UI/Control.h"

namespace Origin {

class Screen : public Control {

public:

    enum class Name {
        Menu,
        Settings,
        Game
    };

    Screen();
    virtual ~Screen();
    virtual void hide();
    virtual void pause();
    virtual void resume();
    virtual void show();

private:
    bool isPaused = true;
};

} // Origin
