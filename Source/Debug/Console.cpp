#include "Console.h"
#include "../Event/Event.h"
#include "../Core/Game.h"
#include "../Core/App.h"
#include <glm/glm.hpp>

Console::Console() {
    Event::getInstance()->windowResize.connect<Console, &Console::onWindowResize>(this);
    visible = false;
}

void Console::draw(float dt) {
    cmdLine.draw(dt);
}

void Console::setVisible(bool visible) {
    this->visible = visible;
    if (visible) {
        cmdLine.setText("/");
        Event::getInstance()->keyPress.connect<Console, &Console::keyPress>(this);
    } else {
        Event::getInstance()->keyPress.disconnect<Console, &Console::keyPress>(this);
    }
}

void Console::onWindowResize(int width, int height) {
    cmdLine.setPosition(glm::vec2(5, height - 5));
}

void Console::keyPress(const SDL_KeyboardEvent& event) {
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
