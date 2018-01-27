#pragma once
#include "Gui/Control.h"

namespace Origin {

class Control;

class Screen : public Control {

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
    void draw();
    void resize(uint32_t width, uint32_t height);

private:
    Control* rootControl = nullptr;
    bool isPaused = true;
};

} // Origin
