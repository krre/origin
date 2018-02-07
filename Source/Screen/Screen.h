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

protected:


private:
    void updateImpl(float dt) override;
    void drawImpl() override;
    void postDraw() override;

    bool isPaused = true;
};

} // Origin
