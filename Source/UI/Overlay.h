#pragma once
#include "UI/Control.h"

namespace Origin {

class DebugHUD;

class Overlay : Control {

public:
    Overlay();
    ~Overlay();
    DebugHUD* getDebugHUD() const { return debugHUD; }

private:
    DebugHUD* debugHUD;
};

} // Origin
