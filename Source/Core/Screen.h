#pragma once
#include "Common.h"
#include <vector>

namespace Origin {

class Control;
class RenderWindow;

class Screen {

public:

    enum class Name {
        Menu,
        Settings,
        Game
    };

    Screen();
    ~Screen();
    virtual void hide();
    virtual void pause();
    virtual void resume();
    virtual void show();

    void setRootControl(Control* control);
    Control* getRootControl() const { return rootControl; }

    void update(float dt);
    void resize(uint32_t width, uint32_t height);

private:
    Control* rootControl = nullptr;
    bool isPaused = true;
};

} // Origin
