#include "Toast.h"
#include "Core/Application.h"
#include "Graphics/Render/RenderWindow.h"
#include <glm/glm.hpp>

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
