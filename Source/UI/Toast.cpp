#include "Toast.h"
#include "../Core/App.h"
#include <glm/glm.hpp>

Toast::Toast() {

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

    Uint32 delay = 4000;
    timerId = SDL_AddTimer(delay, &Toast::onTimeElaplsed, this);
}

Uint32 Toast::onTimeElaplsed(Uint32 interval, void* param) {
    Toast *self = reinterpret_cast<Toast*>(param);
    self->setVisible(false);
    return 0;
}
