#include "Toast.h"
#include "../Core/App.h"
#include <glm/glm.hpp>

Toast::Toast() {
    timer.timeout.connectMember(&Toast::onTimeout, this);
}

void Toast::render(float dt) {
    text.setPosition(glm::vec2(10, App::getInstance()->getHeight() / 2.0));
    text.render(dt);
}

void Toast::setVisible(bool visible) {
    this->visible = visible;
}

void Toast::showToast(const std::string& toastText) {
    text.setText(toastText);
    setVisible(true);
    timer.start(4000);
}

void Toast::onTimeout() {
    setVisible(false);
}
