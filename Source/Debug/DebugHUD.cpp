#include "DebugHUD.h"

DebugHUD::DebugHUD() {

}

void DebugHUD::render(float dt) {

}

void DebugHUD::trigger() {
    visible = !visible;
}

void DebugHUD::setVisible(bool visible) {
    this->visible = true;
}
