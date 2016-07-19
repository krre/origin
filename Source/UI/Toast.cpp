#include "Toast.h"
#include "../Core/App.h"
#include <glm/glm.hpp>

Toast::Toast() {
    setVisible(false);
    timer.timeout.connect<Toast, &Toast::onTimeout>(this);
}

void Toast::draw(float dt) {
    text.setPosition(glm::vec2(10, App::getInstance()->getHeight() / 2.0));
    text.draw(dt);
}

void Toast::showToast(const std::string& toastText) {
    text.setText(toastText);
    setVisible(true);
    timer.start(4000);
}

void Toast::onTimeout() {
    setVisible(false);
}
