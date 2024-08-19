#include "Control.h"
#include "screen/Screen.h"
#include "ui/UIManager.h"
#include "base/Window.h"
#include "Layout.h"

Control::Control(Control* parent) : Object(parent) {
    m_uiManager = UIManager::get();
}

void Control::setPosition(const Core::Pos2& position) {
    m_position = position;
    updatePosition();
}

void Control::updatePosition() {
    Control* parent = static_cast<Control*>(Object::parent());

    if (parent) {
        m_absolutePosition = parent->absolutePosition() + m_position;
    } else {
        m_absolutePosition = m_position;
    }

    for (const auto child : children()) {
        Control* control = dynamic_cast<Control*>(child);
        if (control) {
            control->updatePosition();
        }
    }
}

void Control::setSize(const Core::Size& size) {
    m_size = size;

    resizeImpl(size.width, size.height);
}

void Control::setScale(float scale) {
    m_scale = scale;
}

void Control::resize(int width, int height) {
    setSize({ (uint32_t)width, (uint32_t)height });
}

void Control::move(int x, int y) {
    setPosition({ x, y });
}

void Control::markDirty() {
    m_dirty = true;

    Control* parent = dynamic_cast<Control*>(Object::parent());
    if (parent) {
        parent->markDirty();
    }
}

void Control::clearDirty() {
    m_dirty = false;
}

void Control::setVisible(bool visible) {
    if (m_visible == visible) return;
    m_visible = visible;

    Screen* screen = Window::get()->currentScreen();

    if (!visible && screen && screen->activeControl() == this) {
        screen->activate();
    }

    markDirty();
}

void Control::update(float dt) {
    if (!m_visible) return;

    updateImpl(dt);

    for (const auto child : children()) {
        Control* control = dynamic_cast<Control*>(child);
        if (control) {
            control->update(dt);
        }
    }
}

void Control::draw() {
    drawImpl();

    for (Object* child : children()) {
        Control* control = dynamic_cast<Control*>(child);
        if (control && control->visible()) {
            control->draw();
        }
    }

    postDraw();
}

void Control::activate() {
    Window::get()->currentScreen()->setActiveControl(this);
}
