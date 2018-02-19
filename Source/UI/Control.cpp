#include "Control.h"
#include "UIBatch.h"
#include "Screen/Screen.h"
#include "Base/Game.h"
#include "UI/UIManager.h"
#include "Base/Window.h"
#include "Layout.h"
#include <algorithm>

namespace Origin {

Control::Control(Control* parent) : Object(parent) {
    uiManager = Game::getUIManager();
}

Control::~Control() {

}

void Control::setPosition(const Pos2& position) {
    this->position = position;
    updatePosition();
}

void Control::updatePosition() {
    Control* parent = static_cast<Control*>(getParent());

    if (parent) {
        absolutePosition = parent->getAbsolutePosition() + position;
    } else {
        absolutePosition = position;
    }

    for (const auto child : getChildren()) {
        static_cast<Control*>(child)->updatePosition();
    }
}

void Control::setSize(const Size& size) {
    this->size = size;

    resizeImpl(size.width, size.height);
}

void Control::setScale(float scale) {
    this->scale = scale;
}

void Control::resize(int width, int height) {
    setSize({ (uint32_t)width, (uint32_t)height });
}

void Control::move(int x, int y) {
    setPosition({ x, y });
}

void Control::markDirty() {
    dirty = true;

    Control* parent = static_cast<Control*>(getParent());
    if (parent != nullptr) {
        parent->markDirty();
    }
}

void Control::clearDirty() {
    dirty = false;
}

void Control::setVisible(bool visible) {
    if (this->visible == visible) return;
    this->visible = visible;

    Screen* screen = Game::getWindow()->getCurrentScreen();

    if (!visible && screen && screen->getActiveControl() == this) {
        screen->activate();
    }

    markDirty();
}

void Control::update(float dt) {
    if (!visible) return;

    updateImpl(dt);

    for (const auto child : getChildren()) {
        static_cast<Control*>(child)->update(dt);
    }
}

void Control::draw() {
    drawImpl();

    for (Object* child : getChildren()) {
        Control* control = static_cast<Control*>(child);
        if (control->getVisible()) {
            control->draw();
        }
    }

    postDraw();
}

void Control::activate() {
    Game::getWindow()->getCurrentScreen()->setActiveControl(this);
}

} // Origin
