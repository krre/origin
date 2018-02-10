#pragma once
#include "Core/Object.h"

struct SDL_KeyboardEvent;
struct SDL_TextInputEvent;

namespace Origin {

class Control;

class UIManager : public Object {

public:
    UIManager(Object* parent = nullptr);
    ~UIManager();

private:
    void onKeyPressed(const SDL_KeyboardEvent& event);
    void onTextInput(const SDL_TextInputEvent& event);
};

} // Origin
