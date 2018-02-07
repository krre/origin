#include "Toast.h"
#include "Core/Game.h"
#include "Core/Window.h"
#include "Core/Timer.h"
#include "UI/Label.h"
#include <glm/glm.hpp>

namespace Origin {

Toast::Toast(Control* parent) : Control(parent) {
    timer = std::make_unique<Timer>();
    text = new Label(this);
    setVisible(false);
    timer->timeout.connect(this, &Toast::onTimeout);
}

Toast::~Toast() {

}

void Toast::drawImpl() {
    text->setPosition({ 5, (int)Game::getWindow()->getHeight() / 2 });
}

void Toast::updateImpl(float dt) {

}

void Toast::showToast(const std::string& toastText) {
    text->setText(toastText);
    setVisible(true);
    timer->start(4000);
}

void Toast::onTimeout() {
    setVisible(false);
}

} // Origin
