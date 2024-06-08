#pragma once
#include "ui/Control.h"

class Screen : public Control {
public:
    enum class Name {
        Menu,
        Settings,
        Game,
        NewGame,
        LoadGame,
        Wait
    };

    Screen();
    virtual ~Screen();

    virtual void hide();
    virtual void pause();
    virtual void resume();
    virtual void show();

    void setActiveControl(Control* control);
    Control* activeControl() const { return m_activeControl; }

private:
    bool m_isPaused = true;
    Control* m_activeControl = nullptr;
};
