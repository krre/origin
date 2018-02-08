#pragma once
#include "Core/Common.h"

struct SDL_KeyboardEvent;

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

    Control* activeControl = nullptr;

};

} // Origin
