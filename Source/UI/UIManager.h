#pragma once
#include "Core/Common.h"

struct SDL_KeyboardEvent;
struct SDL_TextInputEvent;

namespace Origin {

class Control;

class UIManager {

public:
    UIManager();
    ~UIManager();
    void setActiveControl(Control* control);
    Control* getActiveControl() const { return activeControl; }

private:
    void onKeyPressed(const SDL_KeyboardEvent& event);
    void onTextInput(const SDL_TextInputEvent& event);

    Control* activeControl = nullptr;

};

} // Origin
