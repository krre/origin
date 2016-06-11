#pragma once
#include "../Core/Object.h"
#include <unordered_set>
#include <SDL_keycode.h>

class Input : public Object {

public:
    Input();
    void addKey(SDL_Keycode key);
    void removeKey(SDL_Keycode key);
    bool isKeyPressed(SDL_Keycode key);
private:
    unordered_set<SDL_Keycode> keys;
};
