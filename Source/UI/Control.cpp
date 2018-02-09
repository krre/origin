#include "Control.h"
#include "UIBatch.h"
#include "Screen/Screen.h"
#include "Core/Game.h"
#include "UI/UIManager.h"
#include "Core/Window.h"
#include "Layout.h"
#include <algorithm>

namespace Origin {

Control::Control(Control* parent) {
    setParent(parent);
    uiManager = Game::getUIManager();
}

Control::~Control() {
    if (parent != nullptr) {
        parent->removeChild(this);
    }

    removeChildren();

    if (layout) {
        delete layout;
    }

    if (uiManager->getActiveControl() == this) {
        uiManager->setActiveControl(screen);
    }
}

void Control::setPosition(const Pos2& position) {
    this->position = position;
    updatePosition();
}

void Control::updatePosition() {
    if (parent) {
        absolutePosition = parent->getAbsolutePosition() + position;
    } else {
        absolutePosition = position;
    }

    for (const auto child : children) {
        child->updatePosition();
    }
}

void Control::setSize(const Size& size) {
    this->size = size;
}

void Control::setScale(float scale) {
    this->scale = scale;
}

void Control::resize(int width, int height) {
    size.width = width;
    size.height = height;

    resizeImpl(width, height);

    if (layout != nullptr) {
        layout->resize(width, height);
    }
}

void Control::move(int x, int y) {
    setPosition({ x, y });
}

void Control::markDirty() {
    dirty = true;
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
    updateImpl(dt);

    for (const auto child : children) {
        child->update(dt);
    }

    if (layout) {
        layout->update(dt);
    }
}

void Control::draw() {
    drawImpl();

    for (const auto child : children) {
        if (child->getVisible()) {
            child->draw();
        }
    }

    if (layout) {
        layout->draw();
    }

    postDraw();
}

void Control::setParent(Control* parent) {
    if (this->parent == parent) return;

    // Remove self from children of previous parent
    if (this->parent != nullptr) {
        this->parent->removeChild(this);
    }

    this->parent = parent;

    if (parent != nullptr) {
        parent->addChild(this);
        setScreen(parent->getScreen());
    }
}

void Control::addChild(Control* control) {
    children.push_back(control);
    control->setParent(this);
}

void Control::insertChild(Control* control, int index) {
    int realIndex = std::max(0, std::min(index, (int)children.size() - 1));
    children.insert(children.begin() + realIndex, control);
}

void Control::removeChild(Control* control) {
    children.erase(std::remove(children.begin(), children.end(), control), children.end());
}

void Control::removeChildren() {
    for (int i = children.size() - 1; i >= 0; i--) {
        delete children.at(i);
    }

    children.clear();
}

void Control::setScreen(Screen* screen) {
    this->screen = screen;
    for (const auto child : children) {
        child->setScreen(screen);
    }
}

void Control::setLayout(Layout* layout) {
    this->layout = layout;
    layout->setScreen(getScreen());
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
