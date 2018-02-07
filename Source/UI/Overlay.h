#pragma once
#include "Core/Common.h"

namespace Origin {

class DebugHUD;

class Overlay {

public:
    Overlay();
    ~Overlay();
    DebugHUD* getDebugHUD() const { return debugHUD.get(); }

private:
    std::unique_ptr<DebugHUD> debugHUD;
};

} // Origin
