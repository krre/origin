#pragma once
#include "GameState.h"
#include "../Scene/WorldScene.h"

class PlayState : public GameState {

public:
    PlayState();
    void init()  override;
    void cleanup() override;

    void pause() override;
    void resume() override;

    void draw(float dt) override;
    void update(float dt) override;

private:
    WorldScene worldScene;
};
