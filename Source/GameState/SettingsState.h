#pragma once
#include "GameState.h"
#include "../Scene/MenuScene.h"

class SettingsState : public GameState {

public:
    SettingsState();
    void init()  override;
    void cleanup() override;

    void pause() override;
    void resume() override;

    void draw(float dt) override;
    void update(float dt) override;

private:
    MenuScene menuScene;
};
