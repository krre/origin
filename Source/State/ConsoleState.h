#pragma once
#include "GameState.h"

class ConsoleState : public GameState {

public:
    ConsoleState();
    void init()  override;
    virtual void cleanup() override;

    virtual void pause() override;
    virtual void resume() override;

    virtual void handleEvents() override;
    virtual void update(float dt) override;
    virtual void draw(float dt) override;
};
