#pragma once
#include "UI/Control.h"

namespace Origin {

class Screen : public Control {

public:

    enum class Name {
        Menu,
        Settings,
        Game,
        NewGame,
        LoadGame
    };

    Screen();
    virtual ~Screen();
    virtual void hide();
    virtual void pause();
    virtual void resume();
    virtual void show();

    void setActiveControl(Control* control);
    Control* getActiveControl() const { return activeControl; }

protected:


private:
    bool isPaused = true;
    Control* activeControl = nullptr;
};

} // Origin
