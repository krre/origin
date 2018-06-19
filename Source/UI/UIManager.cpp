#include "UIManager.h"
#include "Control.h"
#include "Base/Game.h"
#include "Base/Window.h"
#include "Screen/Screen.h"
#include "Event/Event.h"
#include "Event/Input.h"
#include "UI/Overlay.h"

namespace Origin {

UIManager::UIManager(Object* parent) : SingleObject(parent) {
    Event::get()->keyPressed.connect(this, &UIManager::onKeyPressed);
    Event::get()->textInput.connect(this, &UIManager::onTextInput);
    Event::get()->mouseButtonAction.connect(this, &UIManager::onMouseButtonAction);
}

UIManager::~UIManager() {

}

void UIManager::onKeyPressed(const SDL_KeyboardEvent& event) {
    if (Input::get()->isKeyAccepted) return;

    Control* activeControl = Window::get()->getCurrentScreen()->getActiveControl();
    if (activeControl && activeControl->getVisible()) {
        activeControl->keyPressed(event);
    }
}

void UIManager::onTextInput(const SDL_TextInputEvent& event) {
    if (Input::get()->isKeyAccepted) return;

    Control* activeControl = Window::get()->getCurrentScreen()->getActiveControl();
    if (activeControl && activeControl->getVisible()) {
        activeControl->textPressed(event);
    }
}

void UIManager::onMouseButtonAction(const SDL_MouseButtonEvent& event) {
    Control* control = Window::get()->getCurrentScreen();
    traverseOverLeaf(control, event);

    Overlay* overlay = Game::getOverlay();
    traverseOverLeaf(overlay, event);
}

void UIManager::traverseOverLeaf(Object* object, const SDL_MouseButtonEvent& event) {
    Control* control = dynamic_cast<Control*>(object);
    if (!control || !control->getVisible()) return;

    int mouseX = event.x;
    int mouseY = event.y;

    int width = control->size.width ? control->size.width : control->contentWidth;
    int height = control->size.height ? control->size.height : control->contentHeight;

    if (mouseX >= control->absolutePosition.x &&
            mouseX <= (control->absolutePosition.x + width) &&
            mouseY >= control->absolutePosition.y &&
            mouseY <= (control->absolutePosition.y + height)) {
        if (control->getChildren().size()) {
            for (Object* child : control->getChildren()) {
                traverseOverLeaf(child, event);
            }
        } else {
            Control* parent = control;
            while (parent) {
                parent->mouseButtonAction(event);
                parent = static_cast<Control*>(parent->getParent());
            }
        }
    } else {
        Control* parent = static_cast<Control*>(control->getParent());
        while (parent) {
            parent->mouseButtonAction(event);
            parent = dynamic_cast<Control*>(parent->getParent());
        }
    }
}

} // Origin
