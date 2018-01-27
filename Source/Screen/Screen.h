#pragma once
#include "UI/Control.h"

namespace Origin {

class UIManager;

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

    UIManager* getUIManager() const { return uiManager.get(); }

private:
    bool isPaused = true;
    std::unique_ptr<UIManager> uiManager;
};

} // Origin
