#pragma once
#include "State.h"

class ConsoleState : public State {

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
