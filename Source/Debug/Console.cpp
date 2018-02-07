#include "Console.h"
#include "Event/Event.h"
#include "Core/Game.h"
#include "Core/Game.h"
#include "UI/Label.h"
#include <glm/glm.hpp>

namespace Origin {

Console::Console() {
    cmdLine = new Label(this);
}

//void Console::setVisible(bool visible) {
//    if (visible) {
//        cmdLine->setText("/");
//        Event::get()->keyPressed.connect<Console, &Console::onKeyPressed>(this);
//    } else {
//        Event::get()->keyPressed.disconnect<Console, &Console::onKeyPressed>(this);
//    }
//}

//void Console::writeCommands(Vulkan::CommandBuffer* commandBuffer) {

//}

//void Console::onWindowResize(int width, int height) {
//    cmdLine->setPosition({ 5, height - 5 });
//}

//void Console::onKeyPressed(const SDL_KeyboardEvent& event) {
//    std::string newText;
//    switch (event.keysym.sym) {
//    case SDLK_BACKSPACE:
//        newText = cmdLine->getText().substr(0, cmdLine->getText().length() - 1);
//        cmdLine->setText(newText);
//        break;
//    case SDLK_RETURN:
//        execute();
//        break;
//    default:
//        newText = cmdLine->getText() + (char)event.keysym.sym;
//        cmdLine->setText(newText);
//        break;
//    }
//}

void Console::execute() {
    std::string command = cmdLine->getText();
    if (command.length() > 0 && command.substr(0, 1) == "/") {
        command = command.substr(1, command.length() - 1);
        if (command == "exit") {
            Game::quit();
        } else if (command == "help") {
            PRINT("help");
        }
//        SceneManager::get()->popScene();
    }
}

} // Origin
