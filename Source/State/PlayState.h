#pragma once
#include "GameState.h"

class PlayState : public GameState {

public:
    PlayState();
    void init()  override;
    virtual void cleanup() = 0;

    virtual void pause() = 0;
    virtual void resume() = 0;

    virtual void handleEvents() = 0;
    virtual void update(float dt) = 0;
    virtual void draw(float dt) = 0;
};
