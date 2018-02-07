#include "Overlay.h"
#include "Debug/DebugHUD.h"

namespace Origin {

Overlay::Overlay() {
    debugHUD = new DebugHUD(this);
}

Overlay::~Overlay() {

}

} // Origin
