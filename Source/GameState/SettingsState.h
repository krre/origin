#pragma once
#include "GameState.h"
#include "../Scene/SettingsScene.h"

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
    SettingsScene settingsScene;
};
