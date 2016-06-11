#include "Input.h"

Input::Input() {

}

void Input::addKey(SDL_Keycode key) {
    keys.insert(key);
}

void Input::removeKey(SDL_Keycode key) {
    keys.erase(key);
}

bool Input::isKeyPressed(SDL_Keycode key) {
    return keys.find(key) != keys.end();
}

void Input::setMousePos(const glm::ivec2& pos) {
    mousePos = pos;
}
