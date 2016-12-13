#pragma once
#include "Scene2D.h"
#include "../UI/Button.h"
#include "../UI/LinearLayout.h"

class SettingsScene : public Scene2D {

public:
    SettingsScene(int width, int height);
    ~SettingsScene();
    void draw(float dt) override;

private:
    void onKeyPressed(const SDL_KeyboardEvent& event);
};
