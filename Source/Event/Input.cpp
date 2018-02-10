#include "Input.h"

namespace Origin {

Input::Input(Object* parent) : Object(parent) {

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

void Input::setRelMousePos(const glm::ivec2& relPos) {
    relMousePos += relPos;
}

void Input::mouseReset() {
    relMousePos = glm::ivec2(0, 0);
}

} // Origin
