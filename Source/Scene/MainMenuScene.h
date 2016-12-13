#pragma once
#include "Scene2D.h"
#include "../UI/Button.h"
#include "../UI/LinearLayout.h"

class MainMenuScene : public Scene2D {

public:
    MainMenuScene(int width, int height);
    ~MainMenuScene();
    void draw(float dt) override;

private:
    void onKeyPressed(const SDL_KeyboardEvent& event);
};
