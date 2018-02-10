#include "Control.h"
#include "UIBatch.h"
#include "Screen/Screen.h"
#include "Core/Game.h"
#include "UI/UIManager.h"
#include "Core/Window.h"
#include "Layout.h"
#include <algorithm>

namespace Origin {

Control::Control(Control* parent) : Object(parent) {
    uiManager = Game::getUIManager();
}

Control::~Control() {
    if (layout) {
        delete layout;
    }
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

    if (layout != nullptr) {
        layout->resize(size.width, size.height);
    }
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

    if (!visible && uiManager->getActiveControl() == this) {
        uiManager->setActiveControl(Game::getWindow()->getCurrentScreen());
    }

    markDirty();
}

void Control::update(float dt) {
    if (!visible) return;

    updateImpl(dt);

    for (const auto child : getChildren()) {
        static_cast<Control*>(child)->update(dt);
    }

    if (layout) {
        layout->update(dt);
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

    if (layout) {
        layout->draw();
    }

    postDraw();
}

void Control::setLayout(Layout* layout) {
    this->layout = layout;
    layout->resize(size.width, size.height);
}

void Control::activate() {
    Game::getUIManager()->setActiveControl(this);
}

void Control::setActive(bool active) {
    this->active = active;
    if (active) {

    }
}

} // Origin
