#pragma once
#include "GameState.h"

class PauseState : public GameState {

public:
    PauseState();
    void init()  override;
    void cleanup() override;

    void pause() override;
    void resume() override;

    void draw(float dt) override;
    void update(float dt) override;
};
