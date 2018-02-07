#include "Overlay.h"
#include "Debug/DebugHUD.h"

namespace Origin {

Overlay::Overlay() {
    debugHUD = std::make_unique<DebugHUD>();
}

Overlay::~Overlay() {

}

} // Origin
