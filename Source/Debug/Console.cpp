#include "Console.h"
#include "../Event/Event.h"
#include "../Core/Game.h"
#include "../Core/App.h"
#include <glm/glm.hpp>

Console::Console() {
    cmdLine.setPosition(glm::vec2(5, 5));
    visible = false;
}

void Console::draw(float dt) {
    cmdLine.draw(dt);
}

void Console::setVisible(bool visible) {
    this->visible = visible;
    if (visible) {
        cmdLine.setText("");
        if (!keyPressId) {
            keyPressId = Event::getInstance()->keyPress.connectMember(&Console::keyPress, this, std::placeholders::_1);
        }
    } else {
//        Event::getInstance()->keyPress.disconnect(keyPressId);
    }
}

void Console::keyPress(const SDL_KeyboardEvent& event) {
    if (!visible) return;

    std::string newText;
    switch (event.keysym.sym) {
    case SDLK_BACKSPACE:
        newText = cmdLine.getText().substr(0, cmdLine.getText().length() - 1);
        cmdLine.setText(newText);
        break;
    case SDLK_RETURN:
        execute();
        break;
    default:
        newText = cmdLine.getText() + (char)event.keysym.sym;
        cmdLine.setText(newText);
        break;
    }
}

void Console::execute() {
    std::string command = cmdLine.getText();
    if (command.length() > 0 && command.substr(0, 1) == "/") {
        command = command.substr(1, command.length() - 1);
        if (command == "exit") {
            App::getInstance()->quit();
        }
        setVisible(false);
        Game::getInstance()->setState(Game::PLAY);
    }
}
