#include "UIManager.h"
#include "Control.h"
#include "Core/Game.h"
#include "Core/Window.h"
#include "Screen/Screen.h"
#include "Event/Event.h"
#include "Event/Input.h"

namespace Origin {

UIManager::UIManager(Object* parent) : Object(parent) {
    Game::getEvent()->keyPressed.connect(this, &UIManager::onKeyPressed);
    Game::getEvent()->textInput.connect(this, &UIManager::onTextInput);
}

UIManager::~UIManager() {

}

void UIManager::onKeyPressed(const SDL_KeyboardEvent& event) {
    if (Game::getInput()->isKeyAccepted) return;

    Control* activeControl = Game::getWindow()->getCurrentScreen()->getActiveControl();
    if (activeControl && activeControl->getVisible()) {
        activeControl->keyPressed(event);
    }
}

void UIManager::onTextInput(const SDL_TextInputEvent& event) {
    if (Game::getInput()->isKeyAccepted) return;

    Control* activeControl = Game::getWindow()->getCurrentScreen()->getActiveControl();
    if (activeControl && activeControl->getVisible()) {
        activeControl->textPressed(event);
    }
}

} // Origin
