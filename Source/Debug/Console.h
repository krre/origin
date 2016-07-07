#pragma once
#include "../Core/Singleton.h"
#include "../UI/Text.h"
#include <SDL.h>

class Console : public Singleton<Console> {

public:
    Console();
    void render(float dt);
    void setVisible(bool visible);
    bool getVisible() { return visible; }

private:
    void keyPress(const SDL_KeyboardEvent& event);

    bool visible = false;
    Text cmdLine;
    int keyPressId;
};
