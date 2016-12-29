#pragma once
#include "../Graphics/Drawable.h"
#include "../UI/Text.h"
#include <SDL.h>

class Console : public CovenantLand::Drawable {

public:
    Console();
    void draw(float dt) override;
    void update(float dt) override;
    void setVisible(bool visible) override;

private:
    void onWindowResize(int width, int height);
    void onKeyPressed(const SDL_KeyboardEvent& event);
    void execute();
    Text cmdLine;
};
