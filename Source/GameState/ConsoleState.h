#pragma once
#include "GameState.h"

class ConsoleState : public GameState {

public:
    ConsoleState();
    void init()  override;
    void cleanup() override;

    void pause() override;
    void resume() override;

    void draw(float dt) override;
    void update(float dt) override;
};
