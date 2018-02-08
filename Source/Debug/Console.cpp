#include "Console.h"
#include "Event/Event.h"
#include "Core/Game.h"
#include "Core/Game.h"
#include "UI/Label.h"
#include <glm/glm.hpp>

namespace Origin {

const std::string SLASH = "/";

Console::Console(Control* parent) : TextEdit(parent) {
    setVisible(false);
    reset();
}

void Console::reset() {
    setText(SLASH);
}

void Console::keyPressed(const SDL_KeyboardEvent& event) {
    TextEdit::keyPressed(event);

    if (event.keysym.sym == SDLK_RETURN) {
        execute();
    } else if (event.keysym.sym == SDLK_ESCAPE) {
        setVisible(false);
    }
}

void Console::execute() {
    std::string command = getText();
    if (command.length() > 0 && command.substr(0, 1) == "/") {
        command = command.substr(1, command.length() - 1);
        if (command == "exit") {
            Game::quit();
        } else if (command == "help") {
            PRINT("help");
        }

        setVisible(false);
    }
}

} // Origin
