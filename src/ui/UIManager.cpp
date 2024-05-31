#include "UIManager.h"
#include "Control.h"
#include "base/Window.h"
#include "screen/Screen.h"
#include "event/Event.h"
#include "event/Input.h"
#include "ui/Overlay.h"
#include <SDL.h>

UIManager::UIManager(Object* parent) : SingleObject(parent) {
    Event::get()->keyPressed.connect(this, &UIManager::onKeyPressed);
    Event::get()->textInput.connect(this, &UIManager::onTextInput);
    Event::get()->mouseButtonAction.connect(this, &UIManager::onMouseButtonAction);
}

UIManager::~UIManager() {

}

void UIManager::onKeyPressed(const SDL_KeyboardEvent& event) {
    if (Input::get()->isKeyAccepted) return;

    Control* activeControl = Window::get()->currentScreen()->activeControl();
    if (activeControl && activeControl->visible()) {
        activeControl->keyPressed(event);
    }
}

void UIManager::onTextInput(const SDL_TextInputEvent& event) {
    if (Input::get()->isKeyAccepted) return;

    Control* activeControl = Window::get()->currentScreen()->activeControl();
    if (activeControl && activeControl->visible()) {
        activeControl->textPressed(event);
    }
}

void UIManager::onMouseButtonAction(const SDL_MouseButtonEvent& event) {
    traverseOverLeaf(Window::get()->currentScreen(), event);
    traverseOverLeaf(Overlay::get(), event);
}

void UIManager::traverseOverLeaf(Object* object, const SDL_MouseButtonEvent& event) {
    Control* control = dynamic_cast<Control*>(object);
    if (!control || !control->visible()) return;

    int mouseX = event.x;
    int mouseY = event.y;

    int width = control->m_size.width ? control->m_size.width : control->m_contentWidth;
    int height = control->m_size.height ? control->m_size.height : control->m_contentHeight;

    if (mouseX >= control->m_absolutePosition.x &&
            mouseX <= (control->m_absolutePosition.x + width) &&
            mouseY >= control->m_absolutePosition.y &&
            mouseY <= (control->m_absolutePosition.y + height)) {
        if (control->children().size()) {
            for (Object* child : control->children()) {
                traverseOverLeaf(child, event);
            }
        } else {
            Control* parent = control;
            while (parent) {
                parent->mouseButtonAction(event);
                parent = static_cast<Control*>(parent->parent());
            }
        }
    } else {
        Control* parent = static_cast<Control*>(control->parent());
        while (parent) {
            parent->mouseButtonAction(event);
            parent = dynamic_cast<Control*>(parent->parent());
        }
    }
}
