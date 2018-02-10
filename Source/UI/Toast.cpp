#include "Toast.h"
#include "Core/Game.h"
#include "Core/Window.h"
#include "Core/Timer.h"
#include "UI/Label.h"
#include <glm/glm.hpp>

namespace Origin {

Toast::Toast(Control* parent) : Control(parent) {
    timer = new Timer(this);
    text = new Label(this);
    setVisible(false);
    timer->timeout.connect(this, &Toast::onTimeout);
}

Toast::~Toast() {

}

void Toast::show(const std::string& toastText) {
    text->setText(toastText);
    setVisible(true);
    timer->start(4000);
}

void Toast::onTimeout() {
    setVisible(false);
}

} // Origin
