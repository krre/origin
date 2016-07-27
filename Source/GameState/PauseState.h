#pragma once
#include "GameState.h"
#include "../UI/Scenes/PauseScene.h"

class PauseState : public GameState {

public:
    PauseState();
    void init()  override;
    void cleanup() override;

    void pause() override;
    void resume() override;

    void draw(float dt) override;
    void update(float dt) override;

private:
    PauseScene pauseScene;
};
