#include "Console.h"
#include "../Event/Event.h"
#include <glm/glm.hpp>

Console::Console() {
    cmdLine.setPosition(glm::vec2(100, 100));
    cmdLine.setText("test");
}

void Console::render(float dt) {
    cmdLine.render(dt);
}

void Console::setVisible(bool visible) {
    this->visible = visible;
    if (visible) {
        keyPressId = Event::getInstance()->keyPress.connectMember(&Console::keyPress, this, std::placeholders::_1);
    } else {
        Event::getInstance()->keyPress.disconnect(keyPressId);
    }
}

void Console::keyPress(const SDL_KeyboardEvent& event) {
    print(event.keysym.sym);
}
