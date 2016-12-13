#pragma once
#include "Scene2D.h"
#include "../UI/Button.h"
#include "../UI/LinearLayout.h"

class MenuScene : public Scene2D {

public:
    MenuScene(int width, int height);
    ~MenuScene();
    void draw(float dt) override;

private:
    void onKeyPressed(const SDL_KeyboardEvent& event);
};
