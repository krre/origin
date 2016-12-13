#pragma once
#include "GameState.h"
#include "../Scene/MenuScene.h"

class MenuState : public GameState {

public:
    MenuState();
    void init()  override;
    void cleanup() override;

    void pause() override;
    void resume() override;

    void draw(float dt) override;
    void update(float dt) override;

private:
    MenuScene menuScene;
};
