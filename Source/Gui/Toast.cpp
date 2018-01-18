#include "Toast.h"
#include "Core/Application.h"
#include "Core/Window.h"
#include <glm/glm.hpp>

namespace Origin {

Toast::Toast() {
    setVisible(false);
    timer.timeout.connect(this, &Toast::onTimeout);
    text.setZ(1.0f);
}

void Toast::draw(float dt) {
    text.setPosition({ 5, (int)Application::get()->getWindow()->getHeight() / 2 });
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

} // Origin
