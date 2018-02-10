#include "UIManager.h"
#include "Control.h"
#include "Core/Game.h"
#include "Event/Event.h"
#include "Event/Input.h"

namespace Origin {

UIManager::UIManager(Object* parent) : Object(parent) {
    Game::getEvent()->keyPressed.connect(this, &UIManager::onKeyPressed);
    Game::getEvent()->textInput.connect(this, &UIManager::onTextInput);
}

UIManager::~UIManager() {

}

void UIManager::setActiveControl(Control* control) {
    if (activeControl) {
        activeControl->setActive(false);
    }

    if (control) {
        control->setActive(true);
    }

    activeControl = control;
}

void UIManager::onKeyPressed(const SDL_KeyboardEvent& event) {
    if (Game::getInput()->isKeyAccepted) return;

    if (activeControl && activeControl->getVisible()) {
        activeControl->keyPressed(event);
    }
}

void UIManager::onTextInput(const SDL_TextInputEvent& event) {
    if (Game::getInput()->isKeyAccepted) return;

    if (activeControl && activeControl->getVisible()) {
        activeControl->textPressed(event);
    }
}

} // Origin
