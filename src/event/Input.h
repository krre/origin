#pragma once
#include <core/SingleObject.h>
#include <SDL_keycode.h>
#include <unordered_set>
#include <glm/glm.hpp>

class Input : public Core::SingleObject<Input> {

public:
    Input(Object* parent = nullptr);
    void addKey(SDL_Keycode key);
    void removeKey(SDL_Keycode key);
    bool isKeyPressed(SDL_Keycode key);
    void setMousePos(const glm::ivec2& pos);
    void setRelMousePos(const glm::ivec2& relPos);
    const glm::ivec2& mousePos() const { return m_mousePos; }
    const glm::ivec2& relMousePos() const { return m_relMousePos; }
    void mouseReset();
    bool isKeyAccepted = false;

private:
    std::unordered_set<SDL_Keycode> m_keys;
    glm::ivec2 m_mousePos;
    glm::ivec2 m_relMousePos;
};
