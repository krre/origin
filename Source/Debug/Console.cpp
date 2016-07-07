#include "Console.h"
#include <glm/glm.hpp>

Console::Console() {
    cmdLine.setPosition(glm::vec2(10, 10));
    cmdLine.setText("test");
}

void Console::render(float dt) {
    cmdLine.render(dt);
}

void Console::setVisible(bool visible) {
    this->visible = visible;
}
