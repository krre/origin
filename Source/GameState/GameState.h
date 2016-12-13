#pragma once
#include "../Core/Object.h"

class GameState : public Object {

public:

    enum Type {
        CONSOLE,
        MENU,
        PAUSE,
        PLAY,
        SETTINGS
    };

    GameState();
    Type getType() const { return type; }
    bool getIsFeezable() const { return isFreezable; }

    virtual void init() = 0;
    virtual void cleanup() = 0;

    virtual void pause() = 0;
    virtual void resume() = 0;

    virtual void update(float dt) = 0;
    virtual void draw(float dt) = 0;

protected:
     Type type;
     bool isFreezable; // State stops updating lower states in stack
};
