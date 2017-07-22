#include "Toast.h"
#include "Core/App.h"
#include "Core/Window.h"
#include <glm/glm.hpp>

Toast::Toast() {
    setVisible(false);
    timer.timeout.connect<Toast, &Toast::onTimeout>(this);
    text.setZ(1.0f);
}

void Toast::draw(float dt) {
    text.setPosition({ 5, App::get()->getWindow()->getHeight() / 2 });
    text.draw(dt);
}

void Toast::update(float dt) {

}

void Toast::showToast(const std::string& toastText) {
    text.setText(toastText);
    setVisible(true);
    timer.start(4000);
}

void Toast::onTimeout() {
    setVisible(false);
}
