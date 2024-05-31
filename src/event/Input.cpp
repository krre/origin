#include "Input.h"

Input::Input(Object* parent) : SingleObject(parent) {

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
    m_mousePos = pos;
}

void Input::setRelMousePos(const glm::ivec2& relPos) {
    m_relMousePos += relPos;
}

void Input::mouseReset() {
    m_relMousePos = glm::ivec2(0, 0);
}
