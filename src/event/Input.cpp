#include "Input.h"

Input::Input(Object* parent) : SingleObject(parent) {

}

void Input::addKey(SDL_Keycode key) {
    m_keys.insert(key);
}

void Input::removeKey(SDL_Keycode key) {
    m_keys.erase(key);
}

bool Input::isKeyPressed(SDL_Keycode key) {
    return m_keys.find(key) != m_keys.end();
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
