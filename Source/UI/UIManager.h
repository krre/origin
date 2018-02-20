#pragma once
#include "Core/Object.h"
#include <functional>

struct SDL_KeyboardEvent;
struct SDL_TextInputEvent;
struct SDL_MouseButtonEvent;

namespace Origin {

class UIManager : public Object {

public:
    UIManager(Object* parent = nullptr);
    ~UIManager();

private:
    void onKeyPressed(const SDL_KeyboardEvent& event);
    void onTextInput(const SDL_TextInputEvent& event);
    void onMouseButtonAction(const SDL_MouseButtonEvent& event);
    void traverseOverLeaf(Object* object, const SDL_MouseButtonEvent& event);
};

} // Origin
