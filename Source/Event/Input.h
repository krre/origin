#pragma once
#include "../Core/Object.h"
#include <unordered_set>
#include <SDL_keycode.h>
#include <glm/glm.hpp>

class Input : public Object {

public:
    Input();
    void addKey(SDL_Keycode key);
    void removeKey(SDL_Keycode key);
    bool isKeyPressed(SDL_Keycode key);
    void setMousePos(const glm::ivec2& pos);
    const glm::ivec2& getMousePos() const { return mousePos; }
private:
    unordered_set<SDL_Keycode> keys;
    glm::ivec2 mousePos;
};
