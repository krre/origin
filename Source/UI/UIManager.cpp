#include "UIManager.h"
#include "Control.h"
#include "Core/Game.h"
#include "Event/Event.h"
#include "Event/Input.h"

namespace Origin {

UIManager::UIManager() {
    Game::getEvent()->keyPressed.connect(this, &UIManager::onKeyPressed);
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

} // Origin
